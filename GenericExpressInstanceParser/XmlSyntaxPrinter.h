#ifndef XML_SYNTAX_PRINTER_H
#define XML_SYNTAX_PRINTER_H

#include <list>
#include <ostream>

#include "GenericExpressInstanceParser_Global.h"
#include "ExpressInstanceVisitor.h"
#include "ExpressTypes.h"

namespace geip {

class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT XmlSyntaxPrinter : public ExpressInstanceVisitor
{
public:
    XmlSyntaxPrinter(std::ostream& _ofstream);
    virtual ~XmlSyntaxPrinter();

    void print(std::list<EntityInstance*> entities);

    // InstanceVisitor interface
    virtual void visit(const StringInstance* instance) override;
    virtual void visit(const EnumInstance* instance) override;
    virtual void visit(const BooleanInstance* instance) override;
    virtual void visit(const IntegerInstance* instance) override;
    virtual void visit(const RealInstance* instance) override;
    virtual void visit(const AttributeInstance* instance) override;
    virtual void visit(const EntityInstance* instance) override;

private:
    virtual void visitChilds(const ExpressInstance* instance, bool isAttribute);
    void printMargin(void);
    std::string typeToString(ExpressInstance::InstanceType type);

private:
    int m_depth;
    std::ostream& m_ofstream;
};

} //geip

#endif //XML_SYNTAX_PRINTER_H
