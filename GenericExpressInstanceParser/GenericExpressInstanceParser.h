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

    std::list<EntityInstance*> parse(const std::string& string);
    std::list<EntityInstance*> parse(std::istream* inputStream);

    bool hasError();
    int errorCode();
    std::string errorString();

protected:
    friend class ExpressInstanceParser;
    void addRootEntity(EntityInstance* entity);
    void setError(int errorCode, const std::string& errorString);

private:
    void resetError();

private:
    std::list<EntityInstance*> m_entities;
    int m_errorCode;
    std::string m_errorString;
};

} //geip

#endif //GENERIC_EXPRESS_INSTANCE_PARSER_H
