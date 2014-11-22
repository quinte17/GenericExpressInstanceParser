#ifndef XML_SYNTAX_PRINTER_H
#define XML_SYNTAX_PRINTER_H

#include <list>
#include <ostream>

#include "GenericExpressInstanceParser_Global.h"
#include "ExpressInstanceVisitor.h"

namespace exp {

class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT XmlSyntaxPrinter : public ExpressInstanceVisitor
{
public:
    XmlSyntaxPrinter(std::ostream& _ofstream);

    void print(std::list<EntityInstance*> entities);

    // InstanceVisitor interface
    virtual void visit(const StringInstance* instance);
    virtual void visit(const EnumInstance* instance);
    virtual void visit(const BooleanInstance* instance);
    virtual void visit(const IntegerInstance* instance);
    virtual void visit(const RealInstance* instance);
    virtual void visit(const AttributeInstance* instance);
    virtual void visit(const EntityInstance* instance);

private:
    virtual void visitChilds(const ExpressInstance* instance, const std::string& _tag);
    void printMargin(void);

private:
    int m_depth;
    std::ostream& m_ofstream;
};

} //exp

#endif //XML_SYNTAX_PRINTER_H
