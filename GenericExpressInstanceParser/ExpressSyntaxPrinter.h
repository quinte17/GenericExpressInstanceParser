#ifndef EXPRESS_SYNTAX_PRINTER_H
#define EXPRESS_SYNTAX_PRINTER_H

#include <list>
#include <ostream>

#include "GenericExpressInstanceParser_Global.h"
#include "ExpressInstanceVisitor.h"

namespace geip {

class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT ExpressSyntaxPrinter : public ExpressInstanceVisitor
{
public:
    ExpressSyntaxPrinter(std::ostream& _ofstream);
    virtual ~ExpressSyntaxPrinter();

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
    virtual void visitChilds(
            const ExpressInstance* instance,
            const std::string& leftBrace,
            const std::string& rightBrace);
    void printMargin(void);

private:
    int m_depth;
    std::ostream& m_ofstream;
};

} //geip

#endif //EXPRESS_SYNTAX_PRINTER_H
