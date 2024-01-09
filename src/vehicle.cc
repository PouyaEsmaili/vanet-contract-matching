#include <omnetpp.h>
#include "message_m.h"

using namespace omnetpp;

class Vehicle : public cSimpleModule {
private:
    double totalResource;
    double taskDataSize;
    double taskResource;
    double delayConstraint;

protected:
    virtual void initialize() override {
        // get parameters
        totalResource = par("totalResource");
        taskDataSize = par("taskDataSize");
        taskResource = par("taskResource");
        delayConstraint = par("delayConstraint");
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg->isSelfMessage()) {
            // Check if this is the 'prepareContracts' self-message
            if (strcmp(msg->getName(), "prepareTaskMetadata") == 0) {
                prepareTaskMetadata();
            }
        }

        // check if cMessage is of type ContractList
        if (msg->isName("processContractList")) {
            handleContractList(msg);
        }

        delete msg;
    }

    void handleContractList(cMessage *msg) {
        // cast cMessage to ContractList
        ContractList *contractList = check_and_cast<ContractList *>(msg);

        Contract bestContract = Contract();
        int bestContractIndex = -1;
        for (int i = 0; i < contractList->getContractsArraySize(); i++) {
            // get contract from contractList
            Contract contract = contractList->getContracts(i);

            if (contract.getResource() <= totalResource && contract.getReward() >= bestContract.getReward()) {
                bestContract = contract;
                bestContractIndex = i;
            }
        }
        ContractChoice *contractChoice = new ContractChoice("chooseContract");
        contractChoice->setType(bestContractIndex);
        // print contract choice index, resource, and reward, also with index of vehicle
        EV_DEBUG << "Contract choice: " << contractChoice->getType() << " from vehicle: " << getIndex() << " with resource: "
           << bestContract.getResource() << " and reward: " << bestContract.getReward() << endl;
        send(contractChoice, "baseStation$o");

        cMessage *prepTaskMetadataMsg = new cMessage("prepareTaskMetadata");
        scheduleAt(0, prepTaskMetadataMsg);
    }

    void prepareTaskMetadata() {
        TaskMetadata *taskMetadata = new TaskMetadata("handleTaskMetadata");
        taskMetadata->setTaskResource(taskResource);
        taskMetadata->setTaskDataSize(taskDataSize);
        taskMetadata->setDelayConstraint(delayConstraint);
        send(taskMetadata, "baseStation$o");
    }
};

Define_Module(Vehicle);
