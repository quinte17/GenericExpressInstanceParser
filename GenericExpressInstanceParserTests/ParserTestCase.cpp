#include "ParserTestCase.h"

//qt inlcudes
#include <QTest>

//generic express instance parser (geip) includes
#include <GenericExpressInstanceParser.h>
#include <ExpressTypes.h>

ParserTestCase::ParserTestCase(QObject* parent) :
    QObject(parent)
{
}

ParserTestCase::~ParserTestCase()
{

}

void ParserTestCase::initTestCase()
{

}

void ParserTestCase::cleanupTestCase()
{

}

void ParserTestCase::init()
{
    m_parser.reset(new geip::GenericExpressInstanceParser());
}

void ParserTestCase::cleanup()
{

}

void ParserTestCase::test_comments_data()
{
    QTest::addColumn<QString>("comment");

    QTest::newRow("empty comment") << "(**)";
    QTest::newRow("one line comment") << " (*This is a comment*) ";
    QTest::newRow("one line comment with spaces") << " (* This is a comment *) ";
    QTest::newRow("multi line comment") << " (* This is a \n multi line comment *) ";
}

void ParserTestCase::test_comments()
{
    //init test data set
    QFETCH(QString, comment);

    //parse
    std::list<geip::EntityInstance*> entities = m_parser->parse(comment.toStdString());

    //verify
    QCOMPARE(m_parser->hasError(), false);
    QCOMPARE(m_parser->errorCode(), 0);
    QCOMPARE(m_parser->errorString(), std::string(""));

    QCOMPARE(entities.size(), 0ul);

    //delete
    deleteEntities(entities);
}

void ParserTestCase::test_empty_entity_data()
{
    QTest::addColumn<QString>("entity");

    QTest::newRow("entity") << "Entity()";
    QTest::newRow("entity with spaces") << " Entity ( ) ";
    QTest::newRow("entity with new lines") << " Entity\n(\n) ";
}

void ParserTestCase::test_empty_entity()
{
    //init test data set
    QFETCH(QString, entity);

    //parse
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());

    //verify
    QCOMPARE(m_parser->hasError(), false);
    QCOMPARE(m_parser->errorCode(), 0);
    QCOMPARE(m_parser->errorString(), std::string(""));

    QCOMPARE(entities.size(), 1ul);
    std::vector<geip::EntityInstance*> entityVector = toVector(entities);
    QCOMPARE(entityVector[0]->name(), std::string("Entity"));

    //delete
    deleteEntities(entities);
}

void ParserTestCase::test_multiple_entities_in_one_line()
{
    //init test data set
    QString entity = "Entity1() Entity2 (  ) ";

    //parse
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());

    //verify
    QCOMPARE(m_parser->hasError(), false);
    QCOMPARE(m_parser->errorCode(), 0);
    QCOMPARE(m_parser->errorString(), std::string(""));

    QCOMPARE(entities.size(), 2ul);
    std::vector<geip::EntityInstance*> entityVector = toVector(entities);
    QCOMPARE(entityVector[0]->name(), std::string("Entity1"));
    QCOMPARE(entityVector[1]->name(), std::string("Entity2"));

    //delete
    deleteEntities(entities);
}

void ParserTestCase::test_enumType_data()
{
    QTest::addColumn<QString>("entity");

    QTest::newRow("enum") << "Entity(type:=USER)";
    QTest::newRow("enum with spaces") << "Entity(type := USER)";
}

void ParserTestCase::test_enumType()
{
    //init test data set
    QFETCH(QString, entity);

    //parse
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());

    //verify
    QCOMPARE(m_parser->hasError(), false);
    QCOMPARE(m_parser->errorCode(), 0);
    QCOMPARE(m_parser->errorString(), std::string(""));

    QCOMPARE(entities.size(), 1ul);
    std::vector<geip::EntityInstance*> entityVector = toVector(entities);
    geip::EntityInstance* actualEntity = entityVector[0];
    QCOMPARE(actualEntity->childs()->size(), 1ul);
    QCOMPARE(actualEntity->childs()->front()->toString(), std::string("type:=USER"));

    //delete
    deleteEntities(entities);
}

void ParserTestCase::test_stringType()
{
    //init test data set
    QString entity = "Entity(type:=\"USER\")";

    //parse
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());

    //verify
    QCOMPARE(m_parser->hasError(), false);
    QCOMPARE(m_parser->errorCode(), 0);
    QCOMPARE(m_parser->errorString(), std::string(""));

    QCOMPARE(entities.size(), 1ul);
    std::vector<geip::EntityInstance*> entityVector = toVector(entities);
    geip::EntityInstance* actualEntity = entityVector[0];
    QCOMPARE(actualEntity->childs()->size(), 1ul);
    QCOMPARE(actualEntity->childs()->front()->toString(), std::string("type:=\"USER\""));

    //delete
    deleteEntities(entities);
}

void ParserTestCase::test_booleanType_data()
{
    QTest::addColumn<QString>("entity");
    QTest::addColumn<QString>("value");

    QTest::newRow("true") << "Entity(value:=TRUE)" << "TRUE";
    QTest::newRow("false") << "Entity(value:=FALSE)" << "FALSE";
}

void ParserTestCase::test_booleanType()
{
    //init test data set
    QFETCH(QString, entity);
    QFETCH(QString, value);

    //parse
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());

    //verify
    QCOMPARE(m_parser->hasError(), false);
    QCOMPARE(m_parser->errorCode(), 0);
    QCOMPARE(m_parser->errorString(), std::string(""));

    QCOMPARE(entities.size(), 1ul);
    std::vector<geip::EntityInstance*> entityVector = toVector(entities);
    geip::EntityInstance* actualEntity = entityVector[0];
    QCOMPARE(actualEntity->childs()->size(), 1ul);
    QCOMPARE(actualEntity->childs()->front()->toString(), QString("value:=%1").arg(value).toStdString());

    //delete
    deleteEntities(entities);
}

void ParserTestCase::test_integerType_data()
{
    QTest::addColumn<QString>("entity");
    QTest::addColumn<QString>("value");

    QTest::newRow("int") << "Entity(value:=24973)" << "24973";
    QTest::newRow("int+") << "Entity(value:=+24973)" << "+24973";
    QTest::newRow("int-") << "Entity(value:=-24973)" << "-24973";
}

void ParserTestCase::test_integerType()
{
    //init test data set
    QFETCH(QString, entity);
    QFETCH(QString, value);

    //parse
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());

    //verify
    QCOMPARE(m_parser->hasError(), false);
    QCOMPARE(m_parser->errorCode(), 0);
    QCOMPARE(m_parser->errorString(), std::string(""));

    QCOMPARE(entities.size(), 1ul);
    std::vector<geip::EntityInstance*> entityVector = toVector(entities);
    geip::EntityInstance* actualEntity = entityVector[0];
    QCOMPARE(actualEntity->childs()->size(), 1ul);
    QCOMPARE(actualEntity->childs()->front()->toString(), QString("value:=%1").arg(value).toStdString());

    //delete
    deleteEntities(entities);
}

void ParserTestCase::test_realType_data()
{
    QTest::addColumn<QString>("entity");
    QTest::addColumn<QString>("value");

    QTest::newRow("real") << "Entity(value:=24973.44)" << "24973.44";
    QTest::newRow("real+") << "Entity(value:=+123.45)" << "+123.45";
    QTest::newRow("real-") << "Entity(value:=-123.45)" << "-123.45";
}

void ParserTestCase::test_realType()
{
    //init test data set
    QFETCH(QString, entity);
    QFETCH(QString, value);

    //parse
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());

    //verify
    QCOMPARE(m_parser->hasError(), false);
    QCOMPARE(m_parser->errorCode(), 0);
    QCOMPARE(m_parser->errorString(), std::string(""));

    QCOMPARE(entities.size(), 1ul);
    std::vector<geip::EntityInstance*> entityVector = toVector(entities);
    geip::EntityInstance* actualEntity = entityVector[0];
    QCOMPARE(actualEntity->childs()->size(), 1ul);
    QCOMPARE(actualEntity->childs()->front()->toString(), QString("value:=%1").arg(value).toStdString());

    //delete
    deleteEntities(entities);
}

void ParserTestCase::test_stringList_data()
{
    QTest::addColumn<QString>("entity");

    QTest::newRow("one element") << "StringList (elements:= [\"element 1\"])";
    QTest::newRow("one element") << "StringList (elements:= [\"element 1\",\"element 2\"])";
}

void ParserTestCase::test_stringList()
{
    //init test data set
    QFETCH(QString, entity);

    //parse
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());

    //verify
    QCOMPARE(m_parser->hasError(), false);
    QCOMPARE(m_parser->errorCode(), 0);
    QCOMPARE(m_parser->errorString(), std::string(""));

    QCOMPARE(entities.size(), 1ul);

    //delete
    deleteEntities(entities);
}

void ParserTestCase::test_multiple_attributes_data()
{
    QTest::addColumn<QString>("entity");

    QTest::newRow("Pair") << "Pair(key:=591, value:=1900)";
    QTest::newRow("Triple") << "Pair(key:=591, value:=1900, valid:=FALSE)";
    QTest::newRow("Entity as attribute") << "House(key:=Key(number:=591))";
}

void ParserTestCase::test_multiple_attributes()
{
    //init test data set
    QFETCH(QString, entity);

    //parse
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());

    //verify
    QCOMPARE(m_parser->hasError(), false);
    QCOMPARE(m_parser->errorCode(), 0);
    QCOMPARE(m_parser->errorString(), std::string(""));

    QCOMPARE(entities.size(), 1ul);

    //delete
    deleteEntities(entities);
}

void ParserTestCase::test_entityList_data()
{
    QTest::addColumn<QString>("entity");

    QTest::newRow("empty") << "House(keys:=[ ])";
    QTest::newRow("one") << "House(keys:=[Key(number:=591)])";
    QTest::newRow("multiple") << "House(keys:=[Key(number:=1), Key(number:=2)])";
}

void ParserTestCase::test_entityList()
{
    //init test data set
    QFETCH(QString, entity);

    //parse
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());

    //verify
    QCOMPARE(m_parser->hasError(), false);
    QCOMPARE(m_parser->errorCode(), 0);
    QCOMPARE(m_parser->errorString(), std::string(""));

    QCOMPARE(entities.size(), 1ul);

    //delete
    deleteEntities(entities);
}

void ParserTestCase::test_errors_data()
{
    QTest::addColumn<QString>("entity");

    QTest::newRow("assign error") << "Entity(type=USER)";
    QTest::newRow("no entity name") << "(type := USER)";
    QTest::newRow("no opening (") << "Entity type := USER)";
    QTest::newRow("no closing )") << "Entity(type := USER";
}

void ParserTestCase::test_errors()
{
    //init test data set
    QFETCH(QString, entity);

    //parse
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());

    //verify
    QCOMPARE(m_parser->hasError(), true);
    QCOMPARE(m_parser->errorCode(), 1);
    QVERIFY(m_parser->errorString().length() > 0);

    //delete
    deleteEntities(entities);
}

void ParserTestCase::deleteEntities(std::list<geip::EntityInstance*>& entities)
{
    foreach (geip::EntityInstance* entity, entities) {
        delete entity;
    }

    entities.clear();
}

std::vector<geip::EntityInstance*> ParserTestCase::toVector(std::list<geip::EntityInstance *>& entities)
{
    return std::vector<geip::EntityInstance*>(entities.begin(), entities.end());
}
