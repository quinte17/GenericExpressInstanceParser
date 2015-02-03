#include "GenericExpressInstanceParser.h"

#include <fstream>
#include <sstream>
#include <QtDebug>

#include "ExpressInstanceScanner.h"

namespace geip {

GenericExpressInstanceParser::GenericExpressInstanceParser()
{
}

std::list<EntityInstance*> GenericExpressInstanceParser::parse(const std::string& string)
{
    std::istringstream inputStream(string);
    return parse(&inputStream);
}

std::list<EntityInstance *> GenericExpressInstanceParser::parse(std::istream* inputStream)
{
    m_entities.clear();
    resetError();

    geip::ExpressInstanceScanner scanner(inputStream);
    geip::ExpressInstanceParser parser(scanner, *this);
    parser.parse();

    return m_entities;
}

bool GenericExpressInstanceParser::hasError()
{
    return m_errorCode != 0;
}

int GenericExpressInstanceParser::errorCode()
{
    return m_errorCode;
}

std::string GenericExpressInstanceParser::errorString()
{
    return m_errorString;
}

void GenericExpressInstanceParser::addRootEntity(EntityInstance* entity)
{
    m_entities.push_back(entity);
}

void GenericExpressInstanceParser::setError(int errorCode, const std::string& errorString)
{
    m_errorCode = errorCode;
    m_errorString = errorString;
}

void GenericExpressInstanceParser::resetError()
{
    setError(0, "");
}

} //geip
