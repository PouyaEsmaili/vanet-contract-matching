//
// Generated file, do not edit! Created by opp_msgtool 6.0 from message.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "message_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(Contract)

Contract::Contract(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

Contract::Contract(const Contract& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

Contract::~Contract()
{
}

Contract& Contract::operator=(const Contract& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void Contract::copy(const Contract& other)
{
    this->resource = other.resource;
    this->reward = other.reward;
}

void Contract::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->resource);
    doParsimPacking(b,this->reward);
}

void Contract::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->resource);
    doParsimUnpacking(b,this->reward);
}

double Contract::getResource() const
{
    return this->resource;
}

void Contract::setResource(double resource)
{
    this->resource = resource;
}

double Contract::getReward() const
{
    return this->reward;
}

void Contract::setReward(double reward)
{
    this->reward = reward;
}

class ContractDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_resource,
        FIELD_reward,
    };
  public:
    ContractDescriptor();
    virtual ~ContractDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ContractDescriptor)

ContractDescriptor::ContractDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(Contract)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

ContractDescriptor::~ContractDescriptor()
{
    delete[] propertyNames;
}

bool ContractDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Contract *>(obj)!=nullptr;
}

const char **ContractDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ContractDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ContractDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int ContractDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_resource
        FD_ISEDITABLE,    // FIELD_reward
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *ContractDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "resource",
        "reward",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int ContractDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "resource") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reward") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *ContractDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_resource
        "double",    // FIELD_reward
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **ContractDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ContractDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ContractDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Contract *pp = omnetpp::fromAnyPtr<Contract>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ContractDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Contract *pp = omnetpp::fromAnyPtr<Contract>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Contract'", field);
    }
}

const char *ContractDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Contract *pp = omnetpp::fromAnyPtr<Contract>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ContractDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Contract *pp = omnetpp::fromAnyPtr<Contract>(object); (void)pp;
    switch (field) {
        case FIELD_resource: return double2string(pp->getResource());
        case FIELD_reward: return double2string(pp->getReward());
        default: return "";
    }
}

void ContractDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Contract *pp = omnetpp::fromAnyPtr<Contract>(object); (void)pp;
    switch (field) {
        case FIELD_resource: pp->setResource(string2double(value)); break;
        case FIELD_reward: pp->setReward(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Contract'", field);
    }
}

omnetpp::cValue ContractDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Contract *pp = omnetpp::fromAnyPtr<Contract>(object); (void)pp;
    switch (field) {
        case FIELD_resource: return pp->getResource();
        case FIELD_reward: return pp->getReward();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Contract' as cValue -- field index out of range?", field);
    }
}

void ContractDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Contract *pp = omnetpp::fromAnyPtr<Contract>(object); (void)pp;
    switch (field) {
        case FIELD_resource: pp->setResource(value.doubleValue()); break;
        case FIELD_reward: pp->setReward(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Contract'", field);
    }
}

const char *ContractDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ContractDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Contract *pp = omnetpp::fromAnyPtr<Contract>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ContractDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Contract *pp = omnetpp::fromAnyPtr<Contract>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Contract'", field);
    }
}

Register_Class(ContractList)

ContractList::ContractList(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

ContractList::ContractList(const ContractList& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

ContractList::~ContractList()
{
    for (size_t i = 0; i < contracts_arraysize; i++)
        drop(&this->contracts[i]);
    delete [] this->contracts;
}

ContractList& ContractList::operator=(const ContractList& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ContractList::copy(const ContractList& other)
{
    for (size_t i = 0; i < contracts_arraysize; i++)
        drop(&this->contracts[i]);
    delete [] this->contracts;
    this->contracts = (other.contracts_arraysize==0) ? nullptr : new Contract[other.contracts_arraysize];
    contracts_arraysize = other.contracts_arraysize;
    for (size_t i = 0; i < contracts_arraysize; i++) {
        this->contracts[i] = other.contracts[i];
        this->contracts[i].setName(other.contracts[i].getName());
        take(&this->contracts[i]);
    }
}

void ContractList::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    b->pack(contracts_arraysize);
    doParsimArrayPacking(b,this->contracts,contracts_arraysize);
}

void ContractList::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    delete [] this->contracts;
    b->unpack(contracts_arraysize);
    if (contracts_arraysize == 0) {
        this->contracts = nullptr;
    } else {
        this->contracts = new Contract[contracts_arraysize];
        doParsimArrayUnpacking(b,this->contracts,contracts_arraysize);
    }
}

size_t ContractList::getContractsArraySize() const
{
    return contracts_arraysize;
}

const Contract& ContractList::getContracts(size_t k) const
{
    if (k >= contracts_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)contracts_arraysize, (unsigned long)k);
    return this->contracts[k];
}

void ContractList::setContractsArraySize(size_t newSize)
{
    Contract *contracts2 = (newSize==0) ? nullptr : new Contract[newSize];
    size_t minSize = contracts_arraysize < newSize ? contracts_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        contracts2[i] = this->contracts[i];
    for (size_t i = 0; i < contracts_arraysize; i++)
        drop(&this->contracts[i]);
    delete [] this->contracts;
    this->contracts = contracts2;
    contracts_arraysize = newSize;
    for (size_t i = 0; i < contracts_arraysize; i++)
        take(&this->contracts[i]);
}

void ContractList::setContracts(size_t k, const Contract& contracts)
{
    if (k >= contracts_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)contracts_arraysize, (unsigned long)k);
    this->contracts[k] = contracts;
}

void ContractList::insertContracts(size_t k, const Contract& contracts)
{
    if (k > contracts_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)contracts_arraysize, (unsigned long)k);
    size_t newSize = contracts_arraysize + 1;
    Contract *contracts2 = new Contract[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        contracts2[i] = this->contracts[i];
    contracts2[k] = contracts;
    for (i = k + 1; i < newSize; i++)
        contracts2[i] = this->contracts[i-1];
    for (size_t i = 0; i < contracts_arraysize; i++)
        drop(&this->contracts[i]);
    delete [] this->contracts;
    this->contracts = contracts2;
    contracts_arraysize = newSize;
    for (size_t i = 0; i < contracts_arraysize; i++)
        take(&this->contracts[i]);
}

void ContractList::appendContracts(const Contract& contracts)
{
    insertContracts(contracts_arraysize, contracts);
}

void ContractList::eraseContracts(size_t k)
{
    if (k >= contracts_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)contracts_arraysize, (unsigned long)k);
    size_t newSize = contracts_arraysize - 1;
    Contract *contracts2 = (newSize == 0) ? nullptr : new Contract[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        contracts2[i] = this->contracts[i];
    for (i = k; i < newSize; i++)
        contracts2[i] = this->contracts[i+1];
    for (size_t i = 0; i < contracts_arraysize; i++)
        drop(&this->contracts[i]);
    delete [] this->contracts;
    this->contracts = contracts2;
    contracts_arraysize = newSize;
    for (size_t i = 0; i < contracts_arraysize; i++)
        take(&this->contracts[i]);
}

class ContractListDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_contracts,
    };
  public:
    ContractListDescriptor();
    virtual ~ContractListDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ContractListDescriptor)

ContractListDescriptor::ContractListDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ContractList)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

ContractListDescriptor::~ContractListDescriptor()
{
    delete[] propertyNames;
}

bool ContractListDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ContractList *>(obj)!=nullptr;
}

const char **ContractListDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ContractListDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ContractListDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int ContractListDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISRESIZABLE,    // FIELD_contracts
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *ContractListDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "contracts",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int ContractListDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "contracts") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *ContractListDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "Contract",    // FIELD_contracts
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **ContractListDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ContractListDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ContractListDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ContractList *pp = omnetpp::fromAnyPtr<ContractList>(object); (void)pp;
    switch (field) {
        case FIELD_contracts: return pp->getContractsArraySize();
        default: return 0;
    }
}

void ContractListDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ContractList *pp = omnetpp::fromAnyPtr<ContractList>(object); (void)pp;
    switch (field) {
        case FIELD_contracts: pp->setContractsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ContractList'", field);
    }
}

const char *ContractListDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ContractList *pp = omnetpp::fromAnyPtr<ContractList>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ContractListDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ContractList *pp = omnetpp::fromAnyPtr<ContractList>(object); (void)pp;
    switch (field) {
        case FIELD_contracts: return pp->getContracts(i).str();
        default: return "";
    }
}

void ContractListDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ContractList *pp = omnetpp::fromAnyPtr<ContractList>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ContractList'", field);
    }
}

omnetpp::cValue ContractListDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ContractList *pp = omnetpp::fromAnyPtr<ContractList>(object); (void)pp;
    switch (field) {
        case FIELD_contracts: return omnetpp::toAnyPtr(&pp->getContracts(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ContractList' as cValue -- field index out of range?", field);
    }
}

void ContractListDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ContractList *pp = omnetpp::fromAnyPtr<ContractList>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ContractList'", field);
    }
}

const char *ContractListDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_contracts: return omnetpp::opp_typename(typeid(Contract));
        default: return nullptr;
    };
}

omnetpp::any_ptr ContractListDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ContractList *pp = omnetpp::fromAnyPtr<ContractList>(object); (void)pp;
    switch (field) {
        case FIELD_contracts: return omnetpp::toAnyPtr(&pp->getContracts(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ContractListDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ContractList *pp = omnetpp::fromAnyPtr<ContractList>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ContractList'", field);
    }
}

Register_Class(ContractChoice)

ContractChoice::ContractChoice(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

ContractChoice::ContractChoice(const ContractChoice& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

ContractChoice::~ContractChoice()
{
}

ContractChoice& ContractChoice::operator=(const ContractChoice& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ContractChoice::copy(const ContractChoice& other)
{
    this->type = other.type;
}

void ContractChoice::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->type);
}

void ContractChoice::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
}

int ContractChoice::getType() const
{
    return this->type;
}

void ContractChoice::setType(int type)
{
    this->type = type;
}

class ContractChoiceDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
    };
  public:
    ContractChoiceDescriptor();
    virtual ~ContractChoiceDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ContractChoiceDescriptor)

ContractChoiceDescriptor::ContractChoiceDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ContractChoice)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

ContractChoiceDescriptor::~ContractChoiceDescriptor()
{
    delete[] propertyNames;
}

bool ContractChoiceDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ContractChoice *>(obj)!=nullptr;
}

const char **ContractChoiceDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ContractChoiceDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ContractChoiceDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int ContractChoiceDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_type
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *ContractChoiceDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int ContractChoiceDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *ContractChoiceDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_type
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **ContractChoiceDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ContractChoiceDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ContractChoiceDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ContractChoice *pp = omnetpp::fromAnyPtr<ContractChoice>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ContractChoiceDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ContractChoice *pp = omnetpp::fromAnyPtr<ContractChoice>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ContractChoice'", field);
    }
}

const char *ContractChoiceDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ContractChoice *pp = omnetpp::fromAnyPtr<ContractChoice>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ContractChoiceDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ContractChoice *pp = omnetpp::fromAnyPtr<ContractChoice>(object); (void)pp;
    switch (field) {
        case FIELD_type: return long2string(pp->getType());
        default: return "";
    }
}

void ContractChoiceDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ContractChoice *pp = omnetpp::fromAnyPtr<ContractChoice>(object); (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ContractChoice'", field);
    }
}

omnetpp::cValue ContractChoiceDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ContractChoice *pp = omnetpp::fromAnyPtr<ContractChoice>(object); (void)pp;
    switch (field) {
        case FIELD_type: return pp->getType();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ContractChoice' as cValue -- field index out of range?", field);
    }
}

void ContractChoiceDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ContractChoice *pp = omnetpp::fromAnyPtr<ContractChoice>(object); (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ContractChoice'", field);
    }
}

const char *ContractChoiceDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ContractChoiceDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ContractChoice *pp = omnetpp::fromAnyPtr<ContractChoice>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ContractChoiceDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ContractChoice *pp = omnetpp::fromAnyPtr<ContractChoice>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ContractChoice'", field);
    }
}

Register_Class(TaskMetadata)

TaskMetadata::TaskMetadata(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

TaskMetadata::TaskMetadata(const TaskMetadata& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

TaskMetadata::~TaskMetadata()
{
}

TaskMetadata& TaskMetadata::operator=(const TaskMetadata& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void TaskMetadata::copy(const TaskMetadata& other)
{
    this->taskResource = other.taskResource;
    this->taskDataSize = other.taskDataSize;
    this->delayConstraint = other.delayConstraint;
}

void TaskMetadata::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->taskResource);
    doParsimPacking(b,this->taskDataSize);
    doParsimPacking(b,this->delayConstraint);
}

void TaskMetadata::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->taskResource);
    doParsimUnpacking(b,this->taskDataSize);
    doParsimUnpacking(b,this->delayConstraint);
}

double TaskMetadata::getTaskResource() const
{
    return this->taskResource;
}

void TaskMetadata::setTaskResource(double taskResource)
{
    this->taskResource = taskResource;
}

double TaskMetadata::getTaskDataSize() const
{
    return this->taskDataSize;
}

void TaskMetadata::setTaskDataSize(double taskDataSize)
{
    this->taskDataSize = taskDataSize;
}

double TaskMetadata::getDelayConstraint() const
{
    return this->delayConstraint;
}

void TaskMetadata::setDelayConstraint(double delayConstraint)
{
    this->delayConstraint = delayConstraint;
}

class TaskMetadataDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_taskResource,
        FIELD_taskDataSize,
        FIELD_delayConstraint,
    };
  public:
    TaskMetadataDescriptor();
    virtual ~TaskMetadataDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(TaskMetadataDescriptor)

TaskMetadataDescriptor::TaskMetadataDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(TaskMetadata)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

TaskMetadataDescriptor::~TaskMetadataDescriptor()
{
    delete[] propertyNames;
}

bool TaskMetadataDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TaskMetadata *>(obj)!=nullptr;
}

const char **TaskMetadataDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TaskMetadataDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TaskMetadataDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int TaskMetadataDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_taskResource
        FD_ISEDITABLE,    // FIELD_taskDataSize
        FD_ISEDITABLE,    // FIELD_delayConstraint
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *TaskMetadataDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "taskResource",
        "taskDataSize",
        "delayConstraint",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int TaskMetadataDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "taskResource") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "taskDataSize") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "delayConstraint") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *TaskMetadataDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_taskResource
        "double",    // FIELD_taskDataSize
        "double",    // FIELD_delayConstraint
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **TaskMetadataDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TaskMetadataDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TaskMetadataDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TaskMetadata *pp = omnetpp::fromAnyPtr<TaskMetadata>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TaskMetadataDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TaskMetadata *pp = omnetpp::fromAnyPtr<TaskMetadata>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TaskMetadata'", field);
    }
}

const char *TaskMetadataDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TaskMetadata *pp = omnetpp::fromAnyPtr<TaskMetadata>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TaskMetadataDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TaskMetadata *pp = omnetpp::fromAnyPtr<TaskMetadata>(object); (void)pp;
    switch (field) {
        case FIELD_taskResource: return double2string(pp->getTaskResource());
        case FIELD_taskDataSize: return double2string(pp->getTaskDataSize());
        case FIELD_delayConstraint: return double2string(pp->getDelayConstraint());
        default: return "";
    }
}

void TaskMetadataDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TaskMetadata *pp = omnetpp::fromAnyPtr<TaskMetadata>(object); (void)pp;
    switch (field) {
        case FIELD_taskResource: pp->setTaskResource(string2double(value)); break;
        case FIELD_taskDataSize: pp->setTaskDataSize(string2double(value)); break;
        case FIELD_delayConstraint: pp->setDelayConstraint(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TaskMetadata'", field);
    }
}

omnetpp::cValue TaskMetadataDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TaskMetadata *pp = omnetpp::fromAnyPtr<TaskMetadata>(object); (void)pp;
    switch (field) {
        case FIELD_taskResource: return pp->getTaskResource();
        case FIELD_taskDataSize: return pp->getTaskDataSize();
        case FIELD_delayConstraint: return pp->getDelayConstraint();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TaskMetadata' as cValue -- field index out of range?", field);
    }
}

void TaskMetadataDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TaskMetadata *pp = omnetpp::fromAnyPtr<TaskMetadata>(object); (void)pp;
    switch (field) {
        case FIELD_taskResource: pp->setTaskResource(value.doubleValue()); break;
        case FIELD_taskDataSize: pp->setTaskDataSize(value.doubleValue()); break;
        case FIELD_delayConstraint: pp->setDelayConstraint(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TaskMetadata'", field);
    }
}

const char *TaskMetadataDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr TaskMetadataDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TaskMetadata *pp = omnetpp::fromAnyPtr<TaskMetadata>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TaskMetadataDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TaskMetadata *pp = omnetpp::fromAnyPtr<TaskMetadata>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TaskMetadata'", field);
    }
}

Register_Class(TaskAssignment)

TaskAssignment::TaskAssignment(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

TaskAssignment::TaskAssignment(const TaskAssignment& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

TaskAssignment::~TaskAssignment()
{
}

TaskAssignment& TaskAssignment::operator=(const TaskAssignment& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void TaskAssignment::copy(const TaskAssignment& other)
{
    this->fogNodeId = other.fogNodeId;
    this->price = other.price;
}

void TaskAssignment::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->fogNodeId);
    doParsimPacking(b,this->price);
}

void TaskAssignment::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->fogNodeId);
    doParsimUnpacking(b,this->price);
}

int TaskAssignment::getFogNodeId() const
{
    return this->fogNodeId;
}

void TaskAssignment::setFogNodeId(int fogNodeId)
{
    this->fogNodeId = fogNodeId;
}

double TaskAssignment::getPrice() const
{
    return this->price;
}

void TaskAssignment::setPrice(double price)
{
    this->price = price;
}

class TaskAssignmentDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_fogNodeId,
        FIELD_price,
    };
  public:
    TaskAssignmentDescriptor();
    virtual ~TaskAssignmentDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(TaskAssignmentDescriptor)

TaskAssignmentDescriptor::TaskAssignmentDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(TaskAssignment)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

TaskAssignmentDescriptor::~TaskAssignmentDescriptor()
{
    delete[] propertyNames;
}

bool TaskAssignmentDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TaskAssignment *>(obj)!=nullptr;
}

const char **TaskAssignmentDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TaskAssignmentDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TaskAssignmentDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int TaskAssignmentDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_fogNodeId
        FD_ISEDITABLE,    // FIELD_price
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *TaskAssignmentDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "fogNodeId",
        "price",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int TaskAssignmentDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "fogNodeId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "price") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *TaskAssignmentDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_fogNodeId
        "double",    // FIELD_price
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **TaskAssignmentDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TaskAssignmentDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TaskAssignmentDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TaskAssignment *pp = omnetpp::fromAnyPtr<TaskAssignment>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TaskAssignmentDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TaskAssignment *pp = omnetpp::fromAnyPtr<TaskAssignment>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TaskAssignment'", field);
    }
}

const char *TaskAssignmentDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TaskAssignment *pp = omnetpp::fromAnyPtr<TaskAssignment>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TaskAssignmentDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TaskAssignment *pp = omnetpp::fromAnyPtr<TaskAssignment>(object); (void)pp;
    switch (field) {
        case FIELD_fogNodeId: return long2string(pp->getFogNodeId());
        case FIELD_price: return double2string(pp->getPrice());
        default: return "";
    }
}

void TaskAssignmentDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TaskAssignment *pp = omnetpp::fromAnyPtr<TaskAssignment>(object); (void)pp;
    switch (field) {
        case FIELD_fogNodeId: pp->setFogNodeId(string2long(value)); break;
        case FIELD_price: pp->setPrice(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TaskAssignment'", field);
    }
}

omnetpp::cValue TaskAssignmentDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TaskAssignment *pp = omnetpp::fromAnyPtr<TaskAssignment>(object); (void)pp;
    switch (field) {
        case FIELD_fogNodeId: return pp->getFogNodeId();
        case FIELD_price: return pp->getPrice();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TaskAssignment' as cValue -- field index out of range?", field);
    }
}

void TaskAssignmentDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TaskAssignment *pp = omnetpp::fromAnyPtr<TaskAssignment>(object); (void)pp;
    switch (field) {
        case FIELD_fogNodeId: pp->setFogNodeId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_price: pp->setPrice(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TaskAssignment'", field);
    }
}

const char *TaskAssignmentDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr TaskAssignmentDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TaskAssignment *pp = omnetpp::fromAnyPtr<TaskAssignment>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TaskAssignmentDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TaskAssignment *pp = omnetpp::fromAnyPtr<TaskAssignment>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TaskAssignment'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

