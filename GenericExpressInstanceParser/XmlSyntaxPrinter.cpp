#include "XmlSyntaxPrinter.h"

#include "ExpressTypes.h"

namespace geip {

XmlSyntaxPrinter::XmlSyntaxPrinter(std::ostream & _ofstream)
    : m_depth(0)
    , m_ofstream(_ofstream)
{

}

XmlSyntaxPrinter::~XmlSyntaxPrinter()
{

}

void XmlSyntaxPrinter::print(std::list<EntityInstance *> entities)
{
    m_ofstream << "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">";
    m_ofstream << std::endl;

    std::list<geip::EntityInstance*>::const_iterator iterator = entities.begin();
    for(; iterator != entities.end(); ++iterator){
        (*iterator)->visit(*this);
    }

    m_ofstream << "</geip:entities>";
    m_ofstream << std::endl;
}

void XmlSyntaxPrinter::visit(const StringInstance * instance)
{
    m_ofstream << "<![CDATA[" << "\"" << instance->value() << "\""  << "]]>";
}

void XmlSyntaxPrinter::visit(const EnumInstance * instance)
{
    m_ofstream << instance->value();
}

void XmlSyntaxPrinter::visit(const BooleanInstance * instance)
{
    m_ofstream << instance->value();
}

void XmlSyntaxPrinter::visit(const IntegerInstance * instance)
{
    m_ofstream << instance->value();
}

void XmlSyntaxPrinter::visit(const RealInstance * instance)
{
    m_ofstream << instance->value();
}

void XmlSyntaxPrinter::visit(const AttributeInstance * instance)
{
    switch (instance->attributeType()) {
    case AttributeInstance::SingleAttribute:
        printMargin();
        m_ofstream << "<" << instance->name()
                   << " geip:type=\""
                   << typeToString(instance->childs()->front()->type())
                   << "\">";

        if(instance->childs()->front()->type() == ExpressInstance::EntityType){
            m_ofstream << std::endl;
        }

        instance->childs()->front()->visit(*this);

        if(instance->childs()->front()->type() == ExpressInstance::EntityType){
            printMargin();
        }

        m_ofstream << "</" << instance->name() << ">";
        break;
    case AttributeInstance::MultipleAttributes:{
        printMargin();
        m_ofstream << "<" << instance->name()
                   << " geip:type=\"list\">";

        visitChilds(instance, true);
        m_ofstream << std::endl;
        printMargin();
        m_ofstream << "</" << instance->name() << ">";
        break;
    }
    }
}

void XmlSyntaxPrinter::visitChilds(const ExpressInstance * instance, bool isAttribute)
{
    if(!instance->childs()){
        return;
    }

    ++m_depth;
    std::list<ExpressInstance*>::const_iterator iterator = instance->childs()->begin();
    for(int i = 0; iterator != instance->childs()->end(); ++iterator, ++i){
        m_ofstream << std::endl;

        if(isAttribute){
            printMargin();
            m_ofstream << "<geip:entry"
                       << " geip:type=\""
                       << typeToString((*iterator)->type())
                       << "\">";

            if((*iterator)->type() == ExpressInstance::EntityType){
                m_ofstream << std::endl;
            }
        }

        (*iterator)->visit(*this);

        if(isAttribute){
            if((*iterator)->type() == ExpressInstance::EntityType){
                printMargin();
            }

            m_ofstream << "</geip:entry>";
        }
    }
    --m_depth;
}

void XmlSyntaxPrinter::printMargin()
{
    for(int i = 0; i < m_depth; ++i){
        m_ofstream << "  ";
    }
}

std::string XmlSyntaxPrinter::typeToString(ExpressInstance::InstanceType type)
{
    std::string typeAsString;

    switch (type) {
    case ExpressInstance::InstanceType::StringType:
        typeAsString = "string";
        break;
    case ExpressInstance::InstanceType::EnumType:
        typeAsString = "enum";
        break;
    case ExpressInstance::InstanceType::BooleanType:
        typeAsString = "bool";
        break;
    case ExpressInstance::InstanceType::IntegerType:
        typeAsString = "int";
        break;
    case ExpressInstance::InstanceType::RealType:
        typeAsString = "real";
        break;
    case ExpressInstance::InstanceType::AttributeType:
        typeAsString = "attribute";
        break;
    case ExpressInstance::InstanceType::EntityType:
        typeAsString = "entity";
        break;
    }

    return typeAsString;
}

void XmlSyntaxPrinter::visit(const EntityInstance * instance)
{
    //start tag
    ++m_depth;
    printMargin();m_ofstream << "<" << instance->name() << ">";
    visitChilds(instance, false);
    m_ofstream << std::endl;
    printMargin();m_ofstream << "</" << instance->name() << ">";
    --m_depth;
    m_ofstream << std::endl;
}

} //geip
