//
// Generated file, do not edit! Created by opp_msgtool 6.0 from message.msg.
//

#ifndef __MESSAGE_M_H
#define __MESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class Contract;
class ContractList;
class ContractChoice;
class TaskMetadata;
class TaskAssignment;
/**
 * Class generated from <tt>message.msg:1</tt> by opp_msgtool.
 * <pre>
 * message Contract
 * {
 *     double resource; // Required Computation Resource (delta)
 *     double reward; // Corresponding Reward (pi)
 * }
 * </pre>
 */
class Contract : public ::omnetpp::cMessage
{
  protected:
    double resource = 0;
    double reward = 0;

  private:
    void copy(const Contract& other);

  protected:
    bool operator==(const Contract&) = delete;

  public:
    Contract(const char *name=nullptr, short kind=0);
    Contract(const Contract& other);
    virtual ~Contract();
    Contract& operator=(const Contract& other);
    virtual Contract *dup() const override {return new Contract(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual double getResource() const;
    virtual void setResource(double resource);

    virtual double getReward() const;
    virtual void setReward(double reward);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Contract& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Contract& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>message.msg:6</tt> by opp_msgtool.
 * <pre>
 * message ContractList
 * {
 *     Contract contracts[];
 * }
 * </pre>
 */
class ContractList : public ::omnetpp::cMessage
{
  protected:
    Contract *contracts = nullptr;
    size_t contracts_arraysize = 0;

  private:
    void copy(const ContractList& other);

  protected:
    bool operator==(const ContractList&) = delete;

  public:
    ContractList(const char *name=nullptr, short kind=0);
    ContractList(const ContractList& other);
    virtual ~ContractList();
    ContractList& operator=(const ContractList& other);
    virtual ContractList *dup() const override {return new ContractList(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual void setContractsArraySize(size_t size);
    virtual size_t getContractsArraySize() const;
    virtual const Contract& getContracts(size_t k) const;
    virtual Contract& getContractsForUpdate(size_t k) { return const_cast<Contract&>(const_cast<ContractList*>(this)->getContracts(k));}
    virtual void setContracts(size_t k, const Contract& contracts);
    virtual void insertContracts(size_t k, const Contract& contracts);
    [[deprecated]] void insertContracts(const Contract& contracts) {appendContracts(contracts);}
    virtual void appendContracts(const Contract& contracts);
    virtual void eraseContracts(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ContractList& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ContractList& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>message.msg:10</tt> by opp_msgtool.
 * <pre>
 * message ContractChoice
 * {
 *     int type;
 * }
 * </pre>
 */
class ContractChoice : public ::omnetpp::cMessage
{
  protected:
    int type = 0;

  private:
    void copy(const ContractChoice& other);

  protected:
    bool operator==(const ContractChoice&) = delete;

  public:
    ContractChoice(const char *name=nullptr, short kind=0);
    ContractChoice(const ContractChoice& other);
    virtual ~ContractChoice();
    ContractChoice& operator=(const ContractChoice& other);
    virtual ContractChoice *dup() const override {return new ContractChoice(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getType() const;
    virtual void setType(int type);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ContractChoice& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ContractChoice& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>message.msg:14</tt> by opp_msgtool.
 * <pre>
 * message TaskMetadata
 * {
 *     double taskResource;
 *     double taskDataSize;
 *     double delayConstraint;
 * }
 * </pre>
 */
class TaskMetadata : public ::omnetpp::cMessage
{
  protected:
    double taskResource = 0;
    double taskDataSize = 0;
    double delayConstraint = 0;

  private:
    void copy(const TaskMetadata& other);

  protected:
    bool operator==(const TaskMetadata&) = delete;

  public:
    TaskMetadata(const char *name=nullptr, short kind=0);
    TaskMetadata(const TaskMetadata& other);
    virtual ~TaskMetadata();
    TaskMetadata& operator=(const TaskMetadata& other);
    virtual TaskMetadata *dup() const override {return new TaskMetadata(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual double getTaskResource() const;
    virtual void setTaskResource(double taskResource);

    virtual double getTaskDataSize() const;
    virtual void setTaskDataSize(double taskDataSize);

    virtual double getDelayConstraint() const;
    virtual void setDelayConstraint(double delayConstraint);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TaskMetadata& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TaskMetadata& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>message.msg:20</tt> by opp_msgtool.
 * <pre>
 * message TaskAssignment
 * {
 *     int fogNodeId;
 *     double price;
 * }
 * </pre>
 */
class TaskAssignment : public ::omnetpp::cMessage
{
  protected:
    int fogNodeId = 0;
    double price = 0;

  private:
    void copy(const TaskAssignment& other);

  protected:
    bool operator==(const TaskAssignment&) = delete;

  public:
    TaskAssignment(const char *name=nullptr, short kind=0);
    TaskAssignment(const TaskAssignment& other);
    virtual ~TaskAssignment();
    TaskAssignment& operator=(const TaskAssignment& other);
    virtual TaskAssignment *dup() const override {return new TaskAssignment(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getFogNodeId() const;
    virtual void setFogNodeId(int fogNodeId);

    virtual double getPrice() const;
    virtual void setPrice(double price);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TaskAssignment& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TaskAssignment& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline Contract *fromAnyPtr(any_ptr ptr) { return check_and_cast<Contract*>(ptr.get<cObject>()); }
template<> inline ContractList *fromAnyPtr(any_ptr ptr) { return check_and_cast<ContractList*>(ptr.get<cObject>()); }
template<> inline ContractChoice *fromAnyPtr(any_ptr ptr) { return check_and_cast<ContractChoice*>(ptr.get<cObject>()); }
template<> inline TaskMetadata *fromAnyPtr(any_ptr ptr) { return check_and_cast<TaskMetadata*>(ptr.get<cObject>()); }
template<> inline TaskAssignment *fromAnyPtr(any_ptr ptr) { return check_and_cast<TaskAssignment*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __MESSAGE_M_H

