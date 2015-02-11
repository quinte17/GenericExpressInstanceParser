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
    QString expected = "<geip:entities>\n</geip:entities>\n";
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
            "<geip:entities>\n"
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
            "<geip:entities>\n"
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
