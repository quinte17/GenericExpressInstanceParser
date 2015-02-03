#include <QString>
#include <QtTest>

#include "BenchmarkTestCase.h"
#include "ParserTestCase.h"

int main(int argc, char *argv[])
{
    int result = 0;

    BenchmarkTestCase benchmarkTestCase;
    //result += QTest::qExec(&benchmarkTestCase, argc, argv);

    ParserTestCase parserTestCase;
    result += QTest::qExec(&parserTestCase, argc, argv);
}
