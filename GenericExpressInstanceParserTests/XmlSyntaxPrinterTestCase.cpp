#include "XmlSyntaxPrinterTestCase.h"

//qt inlcudes
#include <QTest>
#include <QtDebug>

//generic express instance parser (geip) inclues
#include <GenericExpressInstanceParser.h>
#include <XmlSyntaxPrinter.h>

XmlSyntaxPrinterTestCase::XmlSyntaxPrinterTestCase(QObject * parent)
    : QObject(parent)
{

}

XmlSyntaxPrinterTestCase::~XmlSyntaxPrinterTestCase()
{

}

/*****************************/
//init and cleanup functions
/*****************************/

void XmlSyntaxPrinterTestCase::initTestCase()
{

}

void XmlSyntaxPrinterTestCase::cleanupTestCase()
{

}

void XmlSyntaxPrinterTestCase::init()
{
    m_xmlStream.str(""); //clear the stream

    m_parser.reset(new geip::GenericExpressInstanceParser());
    m_xmlPrinter.reset(new geip::XmlSyntaxPrinter(m_xmlStream));
}

void XmlSyntaxPrinterTestCase::cleanup()
{

}

/*****************************/
//test functions
/*****************************/

void XmlSyntaxPrinterTestCase::test_comments_data()
{
    QTest::addColumn<QString>("comment");

    QTest::newRow("empty comment") << "(**)";
    QTest::newRow("one line comment") << " (*This is a comment*) ";
    QTest::newRow("one line comment with spaces") << " (* This is a comment *) ";
    QTest::newRow("multi line comment") << " (* This is a \n multi line comment *) ";
}

void XmlSyntaxPrinterTestCase::test_comments()
{
    //init test data set
    QFETCH(QString, comment);

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(comment.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected = "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_empty_entity_data()
{
    QTest::addColumn<QString>("entity");

    QTest::newRow("entity") << "Entity()";
    QTest::newRow("entity with spaces") << " Entity ( ) ";
    QTest::newRow("entity with new lines") << " Entity\n(\n) ";
}

void XmlSyntaxPrinterTestCase::test_empty_entity()
{
    //init test data set
    QFETCH(QString, entity);

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <Entity>\n"
            "  </Entity>\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_multiple_entities_in_one_line()
{
    //init test data set
    QString entity = "Entity1() Entity2 (  ) ";

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <Entity1>\n"
            "  </Entity1>\n"
            "  <Entity2>\n"
            "  </Entity2>\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_enumType_data()
{
    QTest::addColumn<QString>("entity");

    QTest::newRow("enum") << "Entity(type:=USER)";
    QTest::newRow("enum with spaces") << "Entity(type := USER)";
}

void XmlSyntaxPrinterTestCase::test_enumType()
{
    //init test data set
    QFETCH(QString, entity);

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <Entity>\n"
            "    <type geip:type=\"enum\">USER</type>\n"
            "  </Entity>\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_stringType_data()
{
    QTest::addColumn<QString>("string");

    QTest::newRow("simple") << "USER";
    QTest::newRow("sentence") << "This is a whole sentence.";
    QTest::newRow("multiple lines") << "This is a whole sentence.\nAnd this sentence goes over\nmultiple lines.";
    QTest::newRow("with xml") << "A String that contains <xml>";
}

void XmlSyntaxPrinterTestCase::test_stringType()
{
    //init test data set
    QFETCH(QString, string);
    QString entity = QString("Entity(data:=\"%1\")").arg(string);

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <Entity>\n"
            "    <data geip:type=\"string\"><![CDATA[\"%1\"]]></data>\n"
            "  </Entity>\n"
            "</geip:entities>\n";
    expected = expected.arg(string);
    QString actual = QString::fromStdString(m_xmlStream.str());
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_booleanType_data()
{
    QTest::addColumn<QString>("entity");
    QTest::addColumn<QString>("value");

    QTest::newRow("true") << "Entity(value:=TRUE)" << "TRUE";
    QTest::newRow("false") << "Entity(value:=FALSE)" << "FALSE";
}

void XmlSyntaxPrinterTestCase::test_booleanType()
{
    //init test data set
    QFETCH(QString, entity);
    QFETCH(QString, value);

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <Entity>\n"
            "    <value geip:type=\"bool\">%1</value>\n"
            "  </Entity>\n"
            "</geip:entities>\n";
    expected = expected.arg(value);
    QString actual = QString::fromStdString(m_xmlStream.str());
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_integerType_data()
{
    QTest::addColumn<QString>("entity");
    QTest::addColumn<QString>("value");

    QTest::newRow("int") << "Entity(value:=24973)" << "24973";
    QTest::newRow("int+") << "Entity(value:=+24973)" << "+24973";
    QTest::newRow("int-") << "Entity(value:=-24973)" << "-24973";
}

void XmlSyntaxPrinterTestCase::test_integerType()
{
    //init test data set
    QFETCH(QString, entity);
    QFETCH(QString, value);

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <Entity>\n"
            "    <value geip:type=\"int\">%1</value>\n"
            "  </Entity>\n"
            "</geip:entities>\n";
    expected = expected.arg(value);
    QString actual = QString::fromStdString(m_xmlStream.str());
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_realType_data()
{
    QTest::addColumn<QString>("entity");
    QTest::addColumn<QString>("value");

    QTest::newRow("real") << "Entity(value:=24973.44)" << "24973.44";
    QTest::newRow("real+") << "Entity(value:=+123.45)" << "+123.45";
    QTest::newRow("real-") << "Entity(value:=-123.45)" << "-123.45";
}

void XmlSyntaxPrinterTestCase::test_realType()
{
    //init test data set
    QFETCH(QString, entity);
    QFETCH(QString, value);

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <Entity>\n"
            "    <value geip:type=\"real\">%1</value>\n"
            "  </Entity>\n"
            "</geip:entities>\n";
    expected = expected.arg(value);
    QString actual = QString::fromStdString(m_xmlStream.str());
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_entityType()
{
    //init test data set
    QString entity = "House(key:=Key(number:=591))";

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <House>\n"
            "    <key geip:type=\"entity\">\n"
            "      <Key>\n"
            "        <number geip:type=\"int\">591</number>\n"
            "      </Key>\n"
            "    </key>\n"
            "  </House>\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
//    qDebug() << "actual: \n" << actual;
//    qDebug() << "expected: \n" << expected;
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_emptyList()
{
    //init test data set
    QString entity = "Entity(types:=[])";

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <Entity>\n"
            "    <types geip:type=\"list\">\n"
            "    </types>\n"
            "  </Entity>\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
//    qDebug() << "actual: \n" << actual;
//    qDebug() << "expected: \n" << expected;
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_enumList()
{
    //init test data set
    QString entity = "EnumList(types:=[TYPE1, TYPE2, TYPE3])";

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <EnumList>\n"
            "    <types geip:type=\"list\">\n"
            "      <geip:entry geip:type=\"enum\">TYPE1</geip:entry>\n"
            "      <geip:entry geip:type=\"enum\">TYPE2</geip:entry>\n"
            "      <geip:entry geip:type=\"enum\">TYPE3</geip:entry>\n"
            "    </types>\n"
            "  </EnumList>\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
//    qDebug() << "actual: \n" << actual;
//    qDebug() << "expected: \n" << expected;
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_stringList()
{
    //init test data set
    QString entity = "StringList (elements:= [\"element 1\",\"element 2\"])";

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <StringList>\n"
            "    <elements geip:type=\"list\">\n"
            "      <geip:entry geip:type=\"string\"><![CDATA[\"element 1\"]]></geip:entry>\n"
            "      <geip:entry geip:type=\"string\"><![CDATA[\"element 2\"]]></geip:entry>\n"
            "    </elements>\n"
            "  </StringList>\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
//    qDebug() << "actual: \n" << actual;
//    qDebug() << "expected: \n" << expected;
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_intList()
{
    //init test data set
    QString entity = "IntList (elements:= [1, 2, 3])";

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <IntList>\n"
            "    <elements geip:type=\"list\">\n"
            "      <geip:entry geip:type=\"int\">1</geip:entry>\n"
            "      <geip:entry geip:type=\"int\">2</geip:entry>\n"
            "      <geip:entry geip:type=\"int\">3</geip:entry>\n"
            "    </elements>\n"
            "  </IntList>\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
//    qDebug() << "actual: \n" << actual;
//    qDebug() << "expected: \n" << expected;
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_realList()
{
    //init test data set
    QString entity = "RealList (elements:= [1.1, 2.2, 3.3])";

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <RealList>\n"
            "    <elements geip:type=\"list\">\n"
            "      <geip:entry geip:type=\"real\">1.1</geip:entry>\n"
            "      <geip:entry geip:type=\"real\">2.2</geip:entry>\n"
            "      <geip:entry geip:type=\"real\">3.3</geip:entry>\n"
            "    </elements>\n"
            "  </RealList>\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
//    qDebug() << "actual: \n" << actual;
//    qDebug() << "expected: \n" << expected;
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_boolList()
{
    //init test data set
    QString entity = "BoolList (elements:= [TRUE, FALSE])";

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <BoolList>\n"
            "    <elements geip:type=\"list\">\n"
            "      <geip:entry geip:type=\"bool\">TRUE</geip:entry>\n"
            "      <geip:entry geip:type=\"bool\">FALSE</geip:entry>\n"
            "    </elements>\n"
            "  </BoolList>\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
//    qDebug() << "actual: \n" << actual;
//    qDebug() << "expected: \n" << expected;
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_multiple_attributes()
{
    //init test data set
    QString entity = "Pair(key:=591, enabled:=TRUE)";

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <Pair>\n"
            "    <key geip:type=\"int\">591</key>\n"
            "    <enabled geip:type=\"bool\">TRUE</enabled>\n"
            "  </Pair>\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
//    qDebug() << "actual: \n" << actual;
//    qDebug() << "expected: \n" << expected;
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_entityList()
{
    //init test data set
    QString entity = "House(keys:=[Key(number:=1), Key(number:=2)])";

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "  <House>\n"
            "    <keys geip:type=\"list\">\n"
            "      <geip:entry geip:type=\"entity\">\n"
            "        <Key>\n"
            "          <number geip:type=\"int\">1</number>\n"
            "        </Key>\n"
            "      </geip:entry>\n"
            "      <geip:entry geip:type=\"entity\">\n"
            "        <Key>\n"
            "          <number geip:type=\"int\">2</number>\n"
            "        </Key>\n"
            "      </geip:entry>\n"
            "    </keys>\n"
            "  </House>\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
//    qDebug() << "actual: \n" << actual;
//    qDebug() << "expected: \n" << expected;
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

void XmlSyntaxPrinterTestCase::test_errors_data()
{
    QTest::addColumn<QString>("entity");

    QTest::newRow("assign error") << "Entity(type=USER)";
    QTest::newRow("no entity name") << "(type := USER)";
    QTest::newRow("no opening (") << "Entity type := USER)";
    QTest::newRow("no closing )") << "Entity(type := USER";
    //QTest::newRow("second entity wrong") << "Entity() Entity(type := USER";
    QTest::newRow("first entity wrong") << "Entity(type=USER) Entity()";
}

void XmlSyntaxPrinterTestCase::test_errors()
{
    //init test data set
    QFETCH(QString, entity);

    //parse and print to xml
    std::list<geip::EntityInstance*> entities = m_parser->parse(entity.toStdString());
    m_xmlPrinter->print(entities);

    //verify
    QString expected =
            "<geip:entities xmlns:geip=\"https://github.com/flo2k/GenericExpressInstanceParser\">\n"
            "</geip:entities>\n";
    QString actual = QString::fromStdString(m_xmlStream.str());
//    qDebug() << "actual: \n" << actual;
//    qDebug() << "expected: \n" << expected;
    QCOMPARE(actual, expected);

    //delete
    deleteEntities(entities);
}

/*****************************/
//helper functions
/*****************************/

void XmlSyntaxPrinterTestCase::deleteEntities(std::list<geip::EntityInstance *> & entities)
{
    foreach (geip::EntityInstance* entity, entities) {
        delete entity;
    }

    entities.clear();
}
