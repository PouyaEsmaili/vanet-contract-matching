#include <omnetpp.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "message_m.h"

using namespace omnetpp;

struct Vehicle {
    double taskResource;
    double taskDataSize;
    double delayConstraint;
    double taskPrice;
    double sharedResource;
    double price;
    bool isTaskReady = false;
    bool isTaskAssigned = false;
    double *totalTime;
};

static size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char *) contents, newLength);
    } catch (std::bad_alloc &e) {
        // handle memory problem
        return 0;
    }
    return newLength;
}

class BaseStation : public cSimpleModule {
private:
    // Contrct
    double unitBenefit;
    double computationCapability;
    int duration;
    std::vector<double> typeProbability;
    int totalVehicles;
    double deltaMin;
    double deltaMax;

    // Task Scheduler
    int taskAssignmentThreshold;
    int numVehicles;
    Vehicle *vehicles;

    ContractList *contractList;

protected:
    virtual void initialize() override {
        // Read parameters from .ned file
        unitBenefit = par("unitBenefit");
        computationCapability = par("computationCapability");
        duration = par("duration");
        totalVehicles = par("totalVehicles");
        deltaMin = par("deltaMin");
        deltaMax = par("deltaMax");

        cStringTokenizer tokenizer(par("typeProbability"), ",");
        while (tokenizer.hasMoreTokens()) {
            typeProbability.push_back(std::stod(tokenizer.nextToken()));
        }

        taskAssignmentThreshold = par("taskAssignmentThreshold");

        numVehicles = gateSize("vehicles");
        vehicles = new Vehicle[numVehicles];

        cMessage *prepContractsMsg = new cMessage("prepareContracts");
        scheduleAt(0, prepContractsMsg);
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg->isSelfMessage()) {
            // Check if this is the 'prepareContracts' self-message
            if (strcmp(msg->getName(), "prepareContracts") == 0) {
                // Call the function to prepare contracts
                prepareContracts();
            }
        }

        else if (msg->isName("handleTaskMetadata")) {
            handleTaskMetadata(msg);
        } else if (msg->isName("chooseContract")) {
            chooseContract(msg);
        }

        delete msg;
    }

    void prepareContracts() {
        CURL *curl;
        CURLcode res;
        std::string readBuffer;

        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json"); // Add Content-Type header
        // Construct JSON payload
        nlohmann::json data = {
                {"unit_benefit",           unitBenefit},
                {"computation_capability", computationCapability},
                {"duration",               duration},
                {"type_probability",       typeProbability},
                {"total_vehicles",         totalVehicles},
                {"delta_min",              deltaMin},
                {"delta_max",              deltaMax}};
        std::string jsonData = data.dump();

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:9090");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonData.size());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            res = curl_easy_perform(curl);

            if (res == CURLE_OK) {
                nlohmann::json responseJson = nlohmann::json::parse(readBuffer);
                sendContractListToVehicles(responseJson);
            } else {
                EV << "curl_easy_perform() failed: " << curl_easy_strerror(res);
            }

            curl_easy_cleanup(curl);
        }
    }

    void sendContractListToVehicles(const nlohmann::json &responseJson) {
        auto deltas = responseJson["delta"];
        auto pies = responseJson["pie"];

        // Create a new ContractList message
        contractList = new ContractList("processContractList");
        contractList->setContractsArraySize(deltas.size());

        for (size_t i = 0; i < deltas.size(); ++i) {
            Contract contract;
            contract.setResource(deltas[i]);
            contract.setReward(pies[i]);
            contractList->setContracts(i, contract);
        }

        // Send the ContractList message to all connected vehicles
        for (int i = 0; i < gateSize("vehicles"); ++i) {
            send(contractList->dup(), "vehicles$o", i);
        }
    }

    void chooseContract(cMessage *msg) {
        ContractChoice *choice = check_and_cast<ContractChoice *>(msg);
        int vehicleId = msg->getArrivalGate()->getIndex();
        int type = choice->getType();
        vehicles[vehicleId].sharedResource = contractList->getContracts(type).getResource();
        vehicles[vehicleId].price = contractList->getContracts(type).getReward();
    }

    void handleTaskMetadata(cMessage *msg) {
        // cast cMessage to TaskMetadata
        EV << "Handling task metadata..." << endl;
        TaskMetadata *taskMetadata = check_and_cast<TaskMetadata *>(msg);

        int vehicleId = msg->getArrivalGate()->getIndex();
        EV << "Received task metadata from vehicle: " << vehicleId << endl;
        vehicles[vehicleId].taskResource = taskMetadata->getTaskResource();
        vehicles[vehicleId].taskDataSize = taskMetadata->getTaskDataSize();
        vehicles[vehicleId].delayConstraint = taskMetadata->getDelayConstraint();
        vehicles[vehicleId].isTaskReady = true;

        int readyVehiclesCount = getReadyVehiclesCount();
        EV << "Ready vehicles count: " << readyVehiclesCount << endl;
        if (readyVehiclesCount >= taskAssignmentThreshold) {
            EV << "Vehicle vehicles[20] = {" << endl;

            for (int i = 0; i < numVehicles; i++) {
                Vehicle vehicle = vehicles[i];
                EV << "    {"
                          << vehicle.taskResource << ", "
                          << vehicle.taskDataSize << ", "
                          << vehicle.delayConstraint << ", "
                          << vehicle.sharedResource << ", "
                          << vehicle.price << ", "
                          << (vehicle.isTaskReady ? "true" : "false");
                EV << "}" << endl;
            }

            EV << "};" << endl;
//            assignTasks();
        }
    }

    int getReadyVehiclesCount() {
        int count = 0;
        for (int i = 0; i < numVehicles; i++) {
            if (vehicles[i].isTaskReady) {
                count++;
            }
        }
        return count;
    }

    void assignTasks() {
        EV << "All vehicles are ready, assigning tasks..." << endl;
        int proposals[numVehicles];

        int remainingTasks = 0;
        for (int i = 0; i < numVehicles; i++) {
            proposals[i] = -1;
            vehicles[i].totalTime = new double[numVehicles];
            if (vehicles[i].isTaskReady) {
                remainingTasks++;
            }
        }

        while (remainingTasks > 0) {
            std::vector<int> assignedIds[numVehicles];
            for (int i = 0; i < numVehicles; i++) {
                if (proposals[i] != -1) {
                    continue;
                }
                double maxPreference = 0;
                int maxPreferenceId = i;
                for (int j = 0; j < numVehicles; j++) {
                    if (i == j) {
                        continue;
                    }
                    vehicles[i].totalTime[j] = vehicles[i].taskResource / vehicles[j].sharedResource;
                    double transmissionTime = getTransmissionTime(i, j);
                    if (transmissionTime > getTransmissionConstraint(i, j)) {
                        continue;
                    }
                    vehicles[i].totalTime[j] += transmissionTime;
                    double preference = 1 / vehicles[i].totalTime[j] - vehicles[j].taskPrice;
                    if (preference > maxPreference || maxPreferenceId == i) {
                        maxPreference = preference;
                        maxPreferenceId = j;
                    }
                }
                proposals[i] = maxPreferenceId;
                assignedIds[maxPreferenceId].push_back(i);
                remainingTasks--;
            }
            for (int i = 0; i < numVehicles; i++) {
                if (assignedIds[i].size() > 1) {
                    for (int j = 0; j < assignedIds[i].size(); j++) {
                        int id = assignedIds[i][j];
                        proposals[id] = -1;
                        remainingTasks++;
                    }
                    vehicles[i].taskPrice += getPriceIncrease(i);
                }
            }
        }

        for (int i = 0; i < numVehicles; i++) {
            if (proposals[i] == -1) {
                continue;
            }
            int nodeId = proposals[i];
            TaskAssignment *taskAssignment = new TaskAssignment();
            taskAssignment->setFogNodeId(nodeId);
            taskAssignment->setPrice(vehicles[nodeId].price);
            send(taskAssignment, "vehicles$o", i);
        }
    }

    double getTransmissionTime(int sourceId, int destinationId) {
        return 0;
    }

    double getTransmissionConstraint(int sourceId, int destinationId) {
        return 1;
    }

    double getPriceIncrease(int id) {
        return 1;
    }
};

Define_Module(BaseStation);
