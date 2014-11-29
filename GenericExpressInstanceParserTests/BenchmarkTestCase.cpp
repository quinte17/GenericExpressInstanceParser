#include "BenchmarkTestCase.h"

//qt inlcudes
#include <QTest>

//stl includes
#include <sstream>

//generic express instance parser (geip) inclues
#include <GenericExpressInstanceParser.h>

BenchmarkTestCase::BenchmarkTestCase(QObject *parent) :
    QObject(parent)
{
}

BenchmarkTestCase::~BenchmarkTestCase()
{

}

void BenchmarkTestCase::initTestCase()
{

}

void BenchmarkTestCase::cleanupTestCase()
{

}

void BenchmarkTestCase::init()
{
    m_parser.reset(new geip::GenericExpressInstanceParser());
}

void BenchmarkTestCase::cleanup()
{

}

void BenchmarkTestCase::benchmark_parsing_data()
{
    QTest::addColumn<int>("loopCount");

    QTest::newRow(".") << 1;
    QTest::newRow("..") << 10;
    QTest::newRow("...") << 100;
    QTest::newRow("....") << 1000;
}

void BenchmarkTestCase::benchmark_parsing()
{
    QFETCH(int, loopCount);

    //init test data set
    std::stringstream instances;
    for(int i = 0; i < loopCount; ++i){
        instances << "Entity()";
        instances << "Entity ( ) Entity()";
        instances << "EnumType(type := USER)";
        instances << "EnumType(type:=\"USER\")";
        instances << "EnumType(type1 := USER, type2 := SYSTEM)";
        instances << "EnumType(type1 := USER, type2 := Entity())";
        instances << "ListType(emptyList := [])";
        instances << "ListType(elements:= [Entity1(), Entity2()])";
        instances << "Pair(key:=\"591\",value:=\"1900\")";
        instances << "Error (number:=24973)";
        instances << "Error (number:=+24973)";
        instances << "Error (number:=-24973)";
        instances << "Error (number:=24973.44)";
        instances << "Error (number:=-123.45)";
        instances << "Error (number:=+123.45)";
        instances << "Min (min:=3.45)";
        instances << "StringList (elements:= [\"element 1\",\"element 2\"])";
        instances << "User(name:=\"aaä\")";
    }

    QBENCHMARK {
        std::list<geip::EntityInstance*> entities = m_parser->parse(instances.str());

        foreach (geip::EntityInstance* entity, entities) {
            delete entity;
        }

        entities.clear();
    }

}
