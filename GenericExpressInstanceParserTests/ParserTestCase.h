#ifndef PARSERTESTCASE_H
#define PARSERTESTCASE_H

//qt inlcudes
#include <QObject>
#include <QSharedPointer>

//stl includes
#include <list>

//forward declaration
namespace geip {
    class GenericExpressInstanceParser;
    class EntityInstance;
}

class ParserTestCase : public QObject
{
    Q_OBJECT
public:
    explicit ParserTestCase(QObject* parent = 0);
    virtual ~ParserTestCase();

    //init and cleanup functions
private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    //test functions
private slots:
    void test_comments_data();
    void test_comments();

    void test_empty_entity_data();
    void test_empty_entity();
    void test_multiple_entities_in_one_line();

    void test_enumType_data();
    void test_enumType();
    void test_stringType();
    void test_booleanType_data();
    void test_booleanType();
    void test_integerType_data();
    void test_integerType();
    void test_realType_data();
    void test_realType();

    void test_stringList_data();
    void test_stringList();
    void test_multiple_attributes_data();
    void test_multiple_attributes();
    void test_entityList_data();
    void test_entityList();

    void test_errors_data();
    void test_errors();

    //helper functions
private:
    void deleteEntities(std::list<geip::EntityInstance*>& entities);
    std::vector<geip::EntityInstance*> toVector(std::list<geip::EntityInstance*>& entities);

private:
    QSharedPointer<geip::GenericExpressInstanceParser> m_parser;
};

#endif // PARSERTESTCASE_H
