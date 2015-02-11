#include "ExpressSyntaxPrinter.h"

#include <iostream>

#include "ExpressTypes.h"

namespace geip {

ExpressSyntaxPrinter::ExpressSyntaxPrinter(std::ostream & _ofstream)
    : m_depth(0)
    , m_ofstream(_ofstream)
{

}

ExpressSyntaxPrinter::~ExpressSyntaxPrinter()
{

}

void ExpressSyntaxPrinter::print(std::list<EntityInstance *> entities)
{
    std::list<geip::EntityInstance*>::const_iterator iterator = entities.begin();
    for(; iterator != entities.end(); ++iterator){
        (*iterator)->visit(*this);
        m_ofstream << std::endl;
    }
}

void ExpressSyntaxPrinter::visit(const StringInstance * instance)
{
    m_ofstream << "\"" << instance->value() << "\"";
}

void ExpressSyntaxPrinter::visit(const EnumInstance * instance)
{
    m_ofstream << instance->value();
}

void ExpressSyntaxPrinter::visit(const BooleanInstance * instance)
{
    m_ofstream << instance->value();
}

void ExpressSyntaxPrinter::visit(const IntegerInstance * instance)
{
    m_ofstream << instance->value();
}

void ExpressSyntaxPrinter::visit(const RealInstance * instance)
{
    m_ofstream << instance->value();
}

void ExpressSyntaxPrinter::visit(const AttributeInstance * instance)
{
    m_ofstream << instance->name() << ":=";

    switch (instance->attributeType()) {
    case AttributeInstance::SingleAttribute:
        instance->childs()->front()->visit(*this);
        break;
    case AttributeInstance::MultipleAttributes:{
        visitChilds(instance, "[", "]");
        break;
    }

    }
}

void ExpressSyntaxPrinter::visitChilds(const ExpressInstance * instance, const std::string & leftBrace, const std::string & rightBrace)
{
    m_ofstream << leftBrace << std::endl;

    if(instance->childs()){
        ++m_depth;
        std::list<ExpressInstance*>::const_iterator iterator = instance->childs()->begin();
        for(int i = 0; iterator != instance->childs()->end(); ++iterator, ++i){
            if(iterator != instance->childs()->begin()){
                m_ofstream << "," << std::endl;
            }

            printMargin();

            (*iterator)->visit(*this);

        }
        m_ofstream << std::endl;
        --m_depth;
    }

    printMargin(); m_ofstream << rightBrace;
}

void ExpressSyntaxPrinter::printMargin()
{
    for(int i = 0; i < m_depth; ++i){
        m_ofstream << "  ";
    }
}

void ExpressSyntaxPrinter::visit(const EntityInstance * instance)
{
    m_ofstream << instance->name();
    visitChilds(instance, "(", ")");
}

} //geip
