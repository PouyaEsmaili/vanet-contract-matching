#include <omnetpp.h>
#include "message_m.h"

using namespace omnetpp;

class Vehicle : public cSimpleModule
{
private:
    double totalResource;
    double taskDataSize;
    double taskResource;
    double delayConstraint;

protected:
    virtual void initialize() override
    {
        // get parameters
        totalResource = par("totalResource");
        taskDataSize = par("taskDataSize");
        taskResource = par("taskResource");
        delayConstraint = par("delayConstraint");
    }

    virtual void handleMessage(cMessage *msg) override
    {
        // check if cMessage is of type ContractList
        if (msg->isName("ContractList"))
        {
            handleContractList(msg);
        }
    }

    void handleContractList(cMessage *msg) {
        // cast cMessage to ContractList
        ContractList *contractList = check_and_cast<ContractList *>(msg);

        Contract bestContract = Contract();
        int bestContractIndex = -1;
        for (int i = 0; i < contractList->getContractsArraySize(); i++)
        {
            // get contract from contractList
            Contract contract = contractList->getContracts(i);

            if (contract.getResource() <= totalResource && contract.getReward() >= bestContract.getReward())
            {
                bestContract = contract;
                bestContractIndex = i;
            }
        }
        ContractChoice *contractChoice = new ContractChoice("ContractChoice");
        contractChoice->setType(bestContractIndex);
        send(contractChoice, "baseStation$o");
    }
};

Define_Module(Vehicle);
