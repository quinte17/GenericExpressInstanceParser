#include "ExpressTypes.h"

#include <sstream>

#include "ExpressInstanceVisitor.h"

namespace geip {

ExpressInstance::ExpressInstance(const ExpressInstance::InstanceType & _type, std::string* _name)
    : m_type(_type)
    , m_name(_name)
    , m_instances(NULL)
{

}

ExpressInstance::ExpressInstance(const ExpressInstance::InstanceType& _type, std::string* _name, ExpressInstance* _instance)
    : m_type(_type)
    , m_name(_name)
    , m_instances(new std::list<ExpressInstance*>())
{
    m_instances->push_back(_instance);
}

ExpressInstance::ExpressInstance(
        const ExpressInstance::InstanceType& _type,
        std::string * _name,
        std::list<ExpressInstance*>* _instances)
    : m_type(_type)
    , m_name(_name)
    , m_instances(_instances)
{

}

ExpressInstance::~ExpressInstance()
{
    delete m_name;
    m_name = NULL;

    if(m_instances){
        while(m_instances->size() > 0){
            ExpressInstance* inst = m_instances->front();
            delete inst;
            inst = NULL;
            m_instances->pop_front();
        }

        delete m_instances;
        m_instances = NULL;
    }
}

ExpressInstance::InstanceType ExpressInstance::type() const
{
    return m_type;
}

const std::list<ExpressInstance *> * ExpressInstance::childs() const
{
    return m_instances;
}

StringInstance::StringInstance(std::string* _value)
    : ExpressInstance(ExpressInstance::StringType, _value)
{

}

StringInstance::~StringInstance()
{

}

std::string StringInstance::value() const
{
    return *m_name;
}

std::string StringInstance::toString() const
{
    std::stringstream instanceString;

    instanceString << "\"" << value() << "\"";

    return instanceString.str();
}

void StringInstance::visit(ExpressInstanceVisitor& visitor) const
{
    visitor.visit(this);
}

EnumInstance::EnumInstance(std::string* _value)
    : ExpressInstance(ExpressInstance::EnumType, _value)
{

}

EnumInstance::~EnumInstance()
{

}

std::string EnumInstance::value() const
{
    return *m_name;
}

std::string EnumInstance::toString() const
{
    std::stringstream instanceString;

    instanceString << value();

    return instanceString.str();
}

void EnumInstance::visit(ExpressInstanceVisitor & visitor) const
{
    visitor.visit(this);
}

BooleanInstance::BooleanInstance(std::string * _value)
    : ExpressInstance(ExpressInstance::BooleanType, _value)
{

}

BooleanInstance::~BooleanInstance()
{

}

std::string BooleanInstance::value() const
{
    return *m_name;
}

std::string BooleanInstance::toString() const
{
    std::stringstream instanceString;

    instanceString << value();

    return instanceString.str();
}

void BooleanInstance::visit(ExpressInstanceVisitor & visitor) const
{
    visitor.visit(this);
}

IntegerInstance::IntegerInstance(std::string * _value)
    : ExpressInstance(ExpressInstance::IntegerType, _value)
{

}

IntegerInstance::~IntegerInstance()
{

}

std::string IntegerInstance::value() const
{
    return *m_name;
}

std::string IntegerInstance::toString() const
{
    std::stringstream instanceString;

    instanceString << value();

    return instanceString.str();
}

void IntegerInstance::visit(ExpressInstanceVisitor & visitor) const
{
    visitor.visit(this);
}

RealInstance::RealInstance(std::string * _value)
    : ExpressInstance(ExpressInstance::RealType, _value)
{

}

RealInstance::~RealInstance()
{

}

std::string RealInstance::value() const
{
    return *m_name;
}

std::string RealInstance::toString() const
{
    std::stringstream instanceString;

    instanceString << value();

    return instanceString.str();
}

void RealInstance::visit(ExpressInstanceVisitor & visitor) const
{
    visitor.visit(this);
}

AttributeInstance::AttributeInstance(std::string* _name, ExpressInstance* _instance)
    : ExpressInstance(ExpressInstance::AttributeType, _name, _instance)
    , m_attributeType(SingleAttribute)
{

}

AttributeInstance::AttributeInstance(std::string* _name, std::list<ExpressInstance*>* _instances)
    : ExpressInstance(ExpressInstance::AttributeType, _name, _instances)
    , m_attributeType(MultipleAttributes)
{

}

AttributeInstance::~AttributeInstance()
{

}

std::string AttributeInstance::name() const
{
    return *m_name;
}

geip::AttributeInstance::AttributeType AttributeInstance::attributeType() const
{
    return m_attributeType;
}

std::string AttributeInstance::toString() const
{
    std::stringstream instanceString;
    instanceString << name() << ":=";

    switch (m_attributeType) {
    case SingleAttribute:
        instanceString << m_instances->front()->toString();
        break;
    case MultipleAttributes:{
        instanceString << "[";

        std::list<ExpressInstance*>::const_iterator iterator = m_instances->begin();
        int i = 0;
        for(; iterator != m_instances->end(); ++iterator, ++i){
            if(iterator != m_instances->begin()){
                instanceString << ",";
            }

            instanceString << (*iterator)->toString();
        }

        instanceString << "]";
    }
        break;
    }

    return instanceString.str();
}

void AttributeInstance::visit(ExpressInstanceVisitor & visitor) const
{
    visitor.visit(this);
}

EntityInstance::EntityInstance(std::string* _name)
    : ExpressInstance(ExpressInstance::EntityType, _name)
{

}

EntityInstance::EntityInstance(
        std::string* _name,
        std::list<ExpressInstance*>* _attributes)
    : ExpressInstance(ExpressInstance::EntityType, _name, _attributes)
{

}

EntityInstance::~EntityInstance()
{

}

std::string EntityInstance::name() const
{
    return *m_name;
}

std::string EntityInstance::toString() const
{
    std::stringstream instanceString;
    instanceString << name() << "(" << std::endl;

    if(m_instances){
        std::list<ExpressInstance*>::const_iterator iterator = m_instances->begin();
        int i = 0;
        for(; iterator != m_instances->end(); ++iterator, ++i){
            if(iterator != m_instances->begin()){
                instanceString << ",";
            }

            instanceString << "  " << (*iterator)->toString();
        }
    }

    instanceString << std::endl << ")";

    return instanceString.str();
}

void EntityInstance::visit(ExpressInstanceVisitor & visitor) const
{
    visitor.visit(this);
}



} //geip
