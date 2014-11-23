#include <QString>
#include <QtTest>

#include "BenchmarkTestCase.h"

int main(int argc, char *argv[])
{
    BenchmarkTestCase benchmarkTestCase;
    return QTest::qExec(&benchmarkTestCase, argc, argv); \
}
