#ifndef EXPRESS_INSTANCE_VISITOR_H
#define EXPRESS_INSTANCE_VISITOR_H

#include "GenericExpressInstanceParser_Global.h"

namespace exp {

//forward declarations
class ExpressInstance;
class StringInstance;
class EnumInstance;
class BooleanInstance;
class IntegerInstance;
class RealInstance;
class AttributeInstance;
class EntityInstance;

class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT ExpressInstanceVisitor
{
public:
    virtual void visit(const StringInstance* instance) = 0;
    virtual void visit(const EnumInstance* instance) = 0;
    virtual void visit(const BooleanInstance* instance) = 0;
    virtual void visit(const IntegerInstance* instance) = 0;
    virtual void visit(const RealInstance* instance) = 0;
    virtual void visit(const AttributeInstance* instance) = 0;
    virtual void visit(const EntityInstance* instance) = 0;
};

} //exp

#endif //EXPRESS_INSTANCE_VISITOR_H
