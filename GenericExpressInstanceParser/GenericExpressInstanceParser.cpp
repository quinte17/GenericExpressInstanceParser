#include "GenericExpressInstanceParser.h"

#include <fstream>
#include <sstream>
#include <QtDebug>

#include "ExpressInstanceScanner.h"

namespace geip {

GenericExpressInstanceParser::GenericExpressInstanceParser()
{
}

std::list<EntityInstance*> GenericExpressInstanceParser::parse(const std::string& _string)
{
    std::istringstream inputStream(_string);
    return parse(&inputStream);
}

std::list<EntityInstance *> GenericExpressInstanceParser::parse(std::istream* _inputStream)
{
    m_entities.clear();

    geip::ExpressInstanceScanner scanner(_inputStream);
    geip::ExpressInstanceParser parser(scanner, *this);
    parser.parse();

    return m_entities;
}

void GenericExpressInstanceParser::addRootEntity(EntityInstance* _entity)
{
    m_entities.push_back(_entity);
}

} //geip
