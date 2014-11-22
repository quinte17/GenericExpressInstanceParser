#include <QCoreApplication>

#include <GenericExpressInstanceParser.h>
#include <ExpressSyntaxPrinter.h>
#include <XmlSyntaxPrinter.h>

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

std::list<exp::EntityInstance*> parseEntitiesInMemory()
{
    exp::GenericExpressInstanceParser parser;

    std::stringstream instances;
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


    std::list<exp::EntityInstance*> entities = parser.parse(instances.str());

    return entities;
}

std::list<exp::EntityInstance*> parseEntitiesFromFile(const std::string& fileName)
{
    exp::GenericExpressInstanceParser parser;

    std::ifstream inputFile;
    inputFile.open(fileName.c_str());
    if(!inputFile.is_open()){
        std::cout << "error opening input file";
        exit(1);
    }

    //parsing
    std::list<exp::EntityInstance*> entities = parser.parse(&inputFile);

    return entities;
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    //parsing
    //std::list<exp::EntityInstance*> entities = parseEntitiesInMemory();

    std::string fileName = std::string(SRCDIR) + "/example_instances_01.txt";
    std::list<exp::EntityInstance*> entities = parseEntitiesFromFile(fileName);

    //printing
    std::ofstream outputFile;
    outputFile.open("test.txt");
    if(!outputFile.is_open()){
        std::cout << "error opening input file";
        return 1;
    }

    exp::ExpressSyntaxPrinter printer(outputFile);
    printer.print(entities);
    exp::XmlSyntaxPrinter xmlPrinter(std::cout);
    xmlPrinter.print(entities);

    outputFile.close();

    //delete entities
    std::list<exp::EntityInstance*>::iterator iterator = entities.begin();
    for(; iterator != entities.end(); ++iterator){
        exp::EntityInstance* entity = *iterator;
        delete entity;
    }
    entities.clear();

    return 0;
}
