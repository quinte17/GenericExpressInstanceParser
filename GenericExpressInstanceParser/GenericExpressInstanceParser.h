#ifndef GENERIC_EXPRESS_INSTANCE_PARSER_H
#define GENERIC_EXPRESS_INSTANCE_PARSER_H

#include <string>
#include <list>

#include "GenericExpressInstanceParser_Global.h"
#include "ExpressTypes.h"

namespace geip {

class GENERIC_EXPRESS_INSTANCE_PARSER_SHARED_EXPORT GenericExpressInstanceParser
{
public:
    GenericExpressInstanceParser();

    std::list<EntityInstance*> parse(const std::string& _string);
    std::list<EntityInstance*> parse(std::istream* _inputStream);

protected:
    friend class ExpressInstanceParser;
    void addRootEntity(EntityInstance* _entity);

private:
    std::list<EntityInstance*> m_entities;
};

} //geip

#endif //GENERIC_EXPRESS_INSTANCE_PARSER_H
