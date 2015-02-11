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
    m_ofstream << "<geip:entities>";
    m_ofstream << std::endl;
    ++m_depth;
    std::list<geip::EntityInstance*>::const_iterator iterator = entities.begin();
    for(; iterator != entities.end(); ++iterator){
        (*iterator)->visit(*this);
    }
    --m_depth;
    m_ofstream << "</geip:entities>" << std::endl;
}

void XmlSyntaxPrinter::visit(const StringInstance * instance)
{
    printMargin();m_ofstream << "<string>" << instance->value() << "</string>";
}

void XmlSyntaxPrinter::visit(const EnumInstance * instance)
{
    printMargin();m_ofstream << "<enum>" << instance->value() << "</enum>";
}

void XmlSyntaxPrinter::visit(const BooleanInstance * instance)
{
    printMargin();m_ofstream << "<bool>" << instance->value() << "</bool>";
}

void XmlSyntaxPrinter::visit(const IntegerInstance * instance)
{
    printMargin();m_ofstream << "<int>" << instance->value() << "</int>";
}

void XmlSyntaxPrinter::visit(const RealInstance * instance)
{
    printMargin();m_ofstream << "<real>" << instance->value() << "</real>";
}

void XmlSyntaxPrinter::visit(const AttributeInstance * instance)
{
    printMargin();m_ofstream << "<attribute name=\"" << instance->name() << "\">";

    ++m_depth;
    switch (instance->attributeType()) {
    case AttributeInstance::SingleAttribute:
        m_ofstream << std::endl;
        instance->childs()->front()->visit(*this);
        break;
    case AttributeInstance::MultipleAttributes:{
        visitChilds(instance, "instances");
        break;
    }
    }
    --m_depth;


    m_ofstream << std::endl;
    printMargin();m_ofstream << "</attribute>";
}

void XmlSyntaxPrinter::visitChilds(const ExpressInstance * instance, const std::string & _tag)
{
    if(!instance->childs()){
        return;
    }

    m_ofstream << std::endl;
    printMargin();m_ofstream << "<" << _tag << ">";

    ++m_depth;
    std::list<ExpressInstance*>::const_iterator iterator = instance->childs()->begin();
    for(int i = 0; iterator != instance->childs()->end(); ++iterator, ++i){
        m_ofstream << std::endl;
        (*iterator)->visit(*this);
    }
    //m_ofstream << std::endl;
    --m_depth;

    m_ofstream << std::endl;
    printMargin();m_ofstream << "</" << _tag << ">";
}

void XmlSyntaxPrinter::printMargin()
{
    for(int i = 0; i < m_depth; ++i){
        m_ofstream << "  ";
    }
}

void XmlSyntaxPrinter::visit(const EntityInstance * instance)
{
    printMargin();m_ofstream << "<" << instance->name() << ">";
    ++m_depth;
    visitChilds(instance, "attributes");
    --m_depth;
    m_ofstream << std::endl;
    printMargin();m_ofstream << "</" << instance->name() << ">";
    m_ofstream << std::endl;
}

} //geip
