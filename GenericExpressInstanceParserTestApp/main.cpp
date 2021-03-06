#include <QCoreApplication>

#include <GenericExpressInstanceParser.h>
#include <ExpressSyntaxPrinter.h>
#include <XmlSyntaxPrinter.h>

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

namespace config {
    enum OutputDialect { // missing c++11 atm
        XML,
        EINST
    };

    class Config {
    public:
        std::string inputFileName;
        std::string outputFileName;
        OutputDialect outputFileType;

        Config() {
            inputFileName = "";
            outputFileName = "";
            outputFileType = XML;  // missing c++11 atm
        }
    };
}

std::list<geip::EntityInstance*> parseEntitiesInMemory()
{
    geip::GenericExpressInstanceParser parser;

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

    std::list<geip::EntityInstance*> entities = parser.parse(instances.str());

    return entities;
}

std::list<geip::EntityInstance*> parseEntitiesFromFile(const std::string& fileName)
{
    geip::GenericExpressInstanceParser parser;

    std::ifstream inputFile;
    inputFile.open(fileName.c_str());
    if(!inputFile.is_open()){
        std::cout << "error opening input file";
        exit(1);
    }

    //parsing
    std::list<geip::EntityInstance*> entities = parser.parse(&inputFile);

    return entities;
}

// qt:qcommandlineparser
config::Config scanParameters(int argc, char *argv[])
{
    config::Config tmpconfig = config::Config();

    for(int i = 1; i < argc; i++) {
        // scan arguments
        // -i inputFile
        // -o outputFile
        // --help
        // -h
        std::string parameter = std::string(argv[i]);
        bool showHelp = false;
        if(parameter == "-i") {
            if(argc <= i+1) {
                showHelp = true;
            } else {
                tmpconfig.inputFileName = argv[i+1];
                i++; // skip next parameter in loop
            }
        } else if (parameter == "-o") {
            if(argc <= i+1) {
                showHelp = true;
            } else {
                tmpconfig.outputFileName = argv[i+1];
                i++; // skip next parameter in loop
            }
        } else if (parameter == "-t") {
            // type of output default xml
            if(argc <= i+1) {
                showHelp = true;
            } else {
                std::string type = argv[i+1];
                if(type == "e") {
                    tmpconfig.outputFileType = config::EINST; // missing c++11 atm
                } else if (type == "x") {
                    tmpconfig.outputFileType = config::XML; // missing c++11 atm
                } else {
                    // unknown type
                    showHelp = true;
                }
                i++; // skip next parameter in loop
            }
        }
        else if (parameter == "--help" || parameter == "-h") {
            showHelp = true;
        } else {
            // unkown Parameter
            std::cerr << "Unknown Parameter: " << parameter << std::endl << std::endl;
            showHelp = true;
        }
        if(showHelp) {
            std::cerr << "Usage:" << std::endl;
            std::cerr << std::string(argv[0]) << " [-i inputFile] [-o outputFile] [-t TYPE]" << std::endl;
            std::cerr << "   if inputFile is omited then stdin is used." << std::endl;
            std::cerr << "   if outputFile is omited then stdout is used." << std::endl;
            std::cerr << "   TYPE is:" << std::endl;
            std::cerr << "       x    for xml output" << std::endl;
            std::cerr << "       e    for expressinstance output" << std::endl;
            std::cerr << std::endl;
            exit(1);
        }
    }
    return tmpconfig;
}

int main(int argc, char *argv[])
{
    //configuration
    config::Config config = scanParameters(argc, argv);

    // Handle inputFile and parse it.
    std::istream* inputStream = 0;
    std::ifstream inputFile;
    if(config.inputFileName == "") {
        // use stdin
        inputStream = &std::cin;
    }
    else {
        inputFile.open(config.inputFileName.c_str());
        if(!inputFile.is_open()){
            std::cout << "error opening input file";
            exit(EXIT_FAILURE);
        }

        inputStream = &inputFile;
    }
    //parsing
    geip::GenericExpressInstanceParser parser;
    std::list<geip::EntityInstance*> entities = parser.parse(inputStream);

    //Close inputfile
    if(inputFile.is_open()){
        inputFile.close();
    }

    // Handle outputFile.
    std::ostream *outputStream = 0;
    std::ofstream outputFile;
    if(config.outputFileName == "") {
        // use stdout
        outputStream = &std::cout;
    } else {
        outputFile.open(config.outputFileName.c_str()); // missing c++11 atm
        if(!outputFile.is_open()){
            std::cerr << "error opening ouput file";
            exit(EXIT_FAILURE);
        }
        outputStream = &outputFile;
    }

    // Handle printing
    if(config.outputFileType == config::XML) { // missing c++11 atm
        geip::XmlSyntaxPrinter xmlPrinter(*outputStream);
        xmlPrinter.print(entities);
    } else if(config.outputFileType == config::EINST) { // missing c++11 atm
        geip::ExpressSyntaxPrinter printer(*outputStream);
        printer.print(entities);
    }

    // Close outfile
    if(outputFile.is_open()){
        outputFile.close();
    }

    //delete entities
    std::list<geip::EntityInstance*>::iterator iterator = entities.begin();
    for(; iterator != entities.end(); ++iterator){
        geip::EntityInstance* entity = *iterator;
        delete entity;
    }
    entities.clear();

    return parser.hasError() ? EXIT_FAILURE : EXIT_SUCCESS;
}
