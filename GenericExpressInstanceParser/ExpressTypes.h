#ifndef EXPRESS_TYPES_H
#define EXPRESS_TYPES_H

#include <string>
#include <list>

#include "GenericExpressInstanceParser_Global.h"

namespace geip {

//forward declaration
class ExpressInstanceVisitor;


class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT ExpressInstance{
public:
    enum InstanceType{
        StringType
       ,EnumType
       ,BooleanType
       ,IntegerType
       ,RealType
       ,AttributeType
       ,EntityType
    };

    ExpressInstance(const InstanceType& _type, std::string * _name);
    ExpressInstance(const InstanceType& _type, std::string * _name, ExpressInstance* _instance);
    ExpressInstance(const InstanceType& _type, std::string * _name, std::list<ExpressInstance*>* _instances);

    virtual ~ExpressInstance(void);

    InstanceType type(void) const;
    const std::list<ExpressInstance*>* childs(void) const;

    virtual std::string toString(void) const = 0;
    virtual void visit(ExpressInstanceVisitor& visitor) const = 0;

protected:
    InstanceType m_type;
    std::string * m_name;
    std::list<ExpressInstance*>* m_instances;
};

class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT StringInstance : public ExpressInstance{
public:
    StringInstance(std::string* _value);
    virtual ~StringInstance(void);

    std::string value(void) const;

    virtual std::string toString(void) const;
    virtual void visit(ExpressInstanceVisitor& visitor) const;
};

class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT EnumInstance : public ExpressInstance{
public:
    EnumInstance(std::string* _value);
    virtual ~EnumInstance(void);

    std::string value(void) const;

    virtual std::string toString(void) const;
    virtual void visit(ExpressInstanceVisitor& visitor) const;
};

class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT BooleanInstance : public ExpressInstance{
public:
    BooleanInstance(std::string* _value);
    virtual ~BooleanInstance(void);

    std::string value(void) const;

    virtual std::string toString(void) const;
    virtual void visit(ExpressInstanceVisitor& visitor) const;
};

class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT IntegerInstance : public ExpressInstance{
public:
    IntegerInstance(std::string* _value);
    virtual ~IntegerInstance(void);

    std::string value(void) const;

    virtual std::string toString(void) const;
    virtual void visit(ExpressInstanceVisitor& visitor) const;
};

class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT RealInstance : public ExpressInstance{
public:
    RealInstance(std::string* _value);
    virtual ~RealInstance(void);

    std::string value(void) const;

    virtual std::string toString(void) const;
    virtual void visit(ExpressInstanceVisitor& visitor) const;
};

class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT AttributeInstance : public ExpressInstance{
public:
    enum AttributeType{
        SingleAttribute
       ,MultipleAttributes
    };

public:
    AttributeInstance(std::string* _name, ExpressInstance* _instance);
    AttributeInstance(std::string* _name, std::list<ExpressInstance*>* _instances);
    virtual ~AttributeInstance(void);

    std::string name(void) const;
    AttributeType attributeType(void) const;

    virtual std::string toString(void) const;
    virtual void visit(ExpressInstanceVisitor& visitor) const;

private:
    AttributeType m_attributeType;
};

class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT EntityInstance : public ExpressInstance{
public:
    EntityInstance(std::string* _name);
    EntityInstance(std::string* _name, std::list<ExpressInstance*>* _attributes);
    virtual ~EntityInstance(void);

    std::string name(void) const;

    virtual std::string toString(void) const;
    virtual void visit(ExpressInstanceVisitor& visitor) const;
};


} //geip

#endif //EXPRESS_TYPES_H
