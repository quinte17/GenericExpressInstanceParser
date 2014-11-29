#ifndef BENCHMARKTESTCASE_H
#define BENCHMARKTESTCASE_H

#include <QObject>
#include <QSharedPointer>

//forward declaration
namespace geip {
    class GenericExpressInstanceParser;
}

class BenchmarkTestCase : public QObject
{
    Q_OBJECT
public:
    explicit BenchmarkTestCase(QObject *parent = 0);
    virtual ~BenchmarkTestCase();

    //init and cleanup functions
private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    //benchmark functions
private slots:
    void benchmark_parsing_data();
    void benchmark_parsing();

private:
    QSharedPointer<geip::GenericExpressInstanceParser> m_parser;
};

#endif // BENCHMARKTESTCASE_H
