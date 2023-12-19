#include <omnetpp.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "message_m.h"

using namespace omnetpp;

struct Vehicle
{
    double taskResource;
    double taskDataSize;
    double delayConstraint;
    double sharedResource;
    double price;
    bool isTaskReady = false;
    double totalTime[];
};

class BaseStation : public cSimpleModule
{
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

protected:
    virtual void initialize() override
    {
        // Read parameters from .ned file
        unitBenefit = par("unitBenefit");
        computationCapability = par("computationCapability");
        duration = par("duration");
        totalVehicles = par("totalVehicles");
        deltaMin = par("deltaMin");
        deltaMax = par("deltaMax");

        cStringTokenizer tokenizer(par("typeProbability"));
        while (tokenizer.hasMoreTokens())
        {
            typeProbability.push_back(std::stod(tokenizer.nextToken()));
        }

        taskAssignmentThreshold = par("taskAssignmentThreshold");

        numVehicles = gate("vehicles")->size();
        vehicles = new Vehicle[numVehicles];

        cMessage *prepContractsMsg = new cMessage("prepareContracts");
        scheduleAt(0, prepContractsMsg);
    }

    virtual void handleMessage(cMessage *msg) override
    {
        if (msg->isSelfMessage())
        {
            // Check if this is the 'prepareContracts' self-message
            if (strcmp(msg->getName(), "prepareContracts") == 0)
            {
                // Call the function to prepare contracts
                prepareContracts();
            }
        }

        // check if cMessage is of type ContractList
        else if (msg->isName("TaskMetadata"))
        {
            handleُTaskMetadata(msg);
        }
        else if (msg->isName("ContractChoice"))
        {
            ContractChoice *choice = check_and_cast<ContractChoice *>(msg);
            EV << "Contract choice: " << choice->getType() << "from vehicle: " << msg->getArrivalGate()->getIndex() << endl;
        }

        delete msg;
    }

    void prepareContracts()
    {
        CURL *curl;
        CURLcode res;
        std::string readBuffer;

        // Construct JSON payload
        nlohmann::json data = {
            {"unit_benefit", unitBenefit},
            {"computation_capability", computationCapability},
            {"duration", duration},
            {"type_probability", typeProbability},
            {"total_vehicles", totalVehicles},
            {"delta_min", deltaMin},
            {"delta_max", deltaMax}};
        std::string jsonData = data.dump();

        curl = curl_easy_init();
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:9090");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonData.size());
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            // Perform the request, res will get the return code
            res = curl_easy_perform(curl);

            if (res == CURLE_OK)
            {
                // Parse the JSON response
                nlohmann::json responseJson = nlohmann::json::parse(readBuffer);
                sendContractListToVehicles(responseJson);
            }
            else
            {
                EV << "curl_easy_perform() failed: " << curl_easy_strerror(res);
            }

            curl_easy_cleanup(curl);
        }
    }

    void sendContractListToVehicles(const nlohmann::json &responseJson)
    {
        auto deltas = responseJson["delta"];
        auto pies = responseJson["pie"];

        // Create a new ContractList message
        ContractList *contractList = new ContractList("contractList");
        contractList->setContractsArraySize(deltas.size());

        for (size_t i = 0; i < deltas.size(); ++i)
        {
            Contract contract;
            contract.setResource(deltas[i]);
            contract.setReward(pies[i]);
            contractList->setContracts(i, contract);
        }

        // Send the ContractList message to all connected vehicles
        for (int i = 0; i < gateSize("vehicles"); ++i)
        {
            send(contractList->dup(), "vehicles$o", i);
        }

        delete contractList;
    }

    void handleُTaskMetadata(cMessage *msg)
    {
        // cast cMessage to TaskMetadata
        TaskMetadata *taskMetadata = check_and_cast<TaskMetadata *>(msg);

        int vehicleId = msg->getArrivalGate()->getIndex();
        vehicles[vehicleId].taskResource = taskMetadata->getTaskResource();
        vehicles[vehicleId].taskDataSize = taskMetadata->getTaskDataSize();
        vehicles[vehicleId].delayConstraint = taskMetadata->getDelayConstraint();
        vehicles[vehicleId].isTaskReady = true;

        if (getReadyVehiclesCount() >= taskAssignmentThreshold)
        {
            assignTasks();
        }
    }

    int getReadyVehiclesCount()
    {
        int count = 0;
        for (int i = 0; i < numVehicles; i++)
        {
            if (vehicles[i].isTaskReady)
            {
                count++;
            }
        }
        return count;
    }

    void assignTasks()
    {
        int proposals[numVehicles];

        int remainingTasks = 0;
        for (int i = 0; i < numVehicles; i++)
        {
            proposals[i] = -1;
            if (vehicles[i].isTaskReady)
            {
                remainingTasks++;
            }
        }

        while (remainingTasks > 0)
        {
            std::vector<int> assignedIds[numVehicles];
            for (int i = 0; i < numVehicles; i++)
            {
                if (proposals[i] != -1)
                {
                    continue;
                }
                int maxPreference = 0;
                int maxPreferenceId = i;
                for (int j = 0; j < numVehicles; j++)
                {
                    if (i == j)
                    {
                        continue;
                    }
                    vehicles[i].totalTime[j] = vehicles[i].taskResource / vehicles[j].sharedResource;
                    double transimissionTime = getTransmissionTime(i, j);
                    if (transimissionTime > getTransimissionConstraint(i, j))
                    {
                        continue;
                    }
                    vehicles[i].totalTime[j] += transimissionTime;
                    double preference = 1 / vehicles[i].totalTime[j] - vehicles[j].price;
                    if (preference > maxPreference || maxPreferenceId == i)
                    {
                        maxPreference = preference;
                        maxPreferenceId = j;
                    }
                }
                proposals[i] = maxPreferenceId;
                assignedIds[maxPreferenceId].push_back(i);
                remainingTasks--;
            }
            for (int i = 0; i < numVehicles; i++)
            {
                if (assignedIds[i].size() > 1)
                {
                    for (int j = 0; j < assignedIds[i].size(); j++)
                    {
                        int id = assignedIds[i][j];
                        proposals[id] = -1;
                        remainingTasks++;
                    }
                    vehicles[i].price += getPriceIncrease(i);
                }
            }
        }

        for (int i = 0; i < numVehicles; i++)
        {
            if (proposals[i] == -1)
            {
                continue;
            }
            int nodeId = proposals[i];
            TaskAssignment *taskAssignment = new TaskAssignment();
            taskAssignment->setFogNodeId(nodeId);
            taskAssignment->setPrice(vehicles[nodeId].price);
            send(taskAssignment, "vehicles$o", i);
        }
    }

    double getTransmissionTime(int sourceId, int destinationId)
    {
        return 0;
    }

    double getTransimissionConstraint(int sourceId, int destinationId)
    {
        return 1;
    }

    double getPriceIncrease(int id)
    {
        return 1;
    }
};

Define_Module(BaseStation);
