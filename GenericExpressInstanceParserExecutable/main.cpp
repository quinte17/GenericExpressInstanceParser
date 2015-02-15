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
        Xml,
        ExpressInstance
    };

    class Config {
    public:
        std::string inputFileName;
        std::string outputFileName;
        OutputDialect outputFileType;

        Config() {
            inputFileName = "";
            outputFileName = "";
            outputFileType = Xml;  // missing c++11 atm
        }
    };
}

// qt:qcommandlineparser
config::Config scanParameters(int argc, char *argv[])
{
    config::Config config = config::Config();

    for(int i = 1; i < argc; i++) {
        // scan arguments
        // -i inputFile
        // -o outputFile
        // -h or --help
        // --version
        // --license
        std::string parameter = std::string(argv[i]);
        bool showHelp = false;
        if(parameter == "-i") {
            if(argc <= i+1) {
                showHelp = true;
            } else {
                config.inputFileName = argv[i+1];
                i++; // skip next parameter in loop
            }
        } else if (parameter == "-o") {
            if(argc <= i+1) {
                showHelp = true;
            } else {
                config.outputFileName = argv[i+1];
                i++; // skip next parameter in loop
            }
        } else if (parameter == "--help" || parameter == "-h") {
            showHelp = true;
        } else if(parameter == "--version") {
            std::cout << "geip version 0.2" << std::endl;
            exit(EXIT_SUCCESS);
        } else if(parameter == "--license") {
            std::cout << "GenericExpressInstanceParser (geip) -- parsing and transforming Express Instance files" << std::endl;
            std::cout << "Version 0.2, 15.02.2015" << std::endl;
            std::cout << "GenericExpressInstanceParser project - (https://github.com/flo2k/GenericExpressInstanceParser)" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "Created: November 2014, Florian Künzner" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "Copyright (C) 2014      Florian Künzner and Stephan Sperber (GenericExpressInstanceParser) (https://github.com/flo2k/GenericExpressInstanceParser)" << std::endl;
            std::cout << "Copyright (C) 2015      Florian Künzner and Stephan Sperber (GenericExpressInstanceParser) (https://github.com/flo2k/GenericExpressInstanceParser)" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "---------------------------------------------------------------------------" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "Condition of use and distribution:" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "This software is provided 'as-is', without any express or implied" << std::endl;
            std::cout << "warranty.  In no event will the authors be held liable for any damages" << std::endl;
            std::cout << "arising from the use of this software." << std::endl;
            std::cout << "" << std::endl;
            std::cout << "Permission is granted to anyone to use this software for any purpose," << std::endl;
            std::cout << "including commercial applications, and to alter it and redistribute it" << std::endl;
            std::cout << "freely, subject to the following restrictions:" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "1. The origin of this software must not be misrepresented; you must not" << std::endl;
            std::cout << "   claim that you wrote the original software. If you use this software" << std::endl;
            std::cout << "   in a product, an acknowledgment in the product documentation would be" << std::endl;
            std::cout << "   appreciated but is not required." << std::endl;
            std::cout << "2. Altered source versions must be plainly marked as such, and must not be" << std::endl;
            std::cout << "   misrepresented as being the original software." << std::endl;
            std::cout << "3. This notice may not be removed or altered from any source distribution." << std::endl;
            std::cout << "" << std::endl;
            std::cout << "---------------------------------------------------------------------------" << std::endl;
            exit(EXIT_SUCCESS);
        } else {
            // unkown Parameter
            std::cerr << "Unknown Parameter: " << parameter << std::endl << std::endl;
            showHelp = true;
        }
        if(showHelp) {
            std::cout << "GenericExpressInstanceParser (geip) -- parsing and transforming Express Instance files" << std::endl;
            std::cout << "" << std::endl;
            std::cerr << "Usage:" << std::endl;
            std::cerr << std::string(argv[0]) << " [-i inputFile] [-o outputFile]" << std::endl;
            std::cerr << "   if inputFile is omitted then stdin is used." << std::endl;
            std::cerr << "   if outputFile is omitted then stdout is used." << std::endl;
            std::cerr << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return config;
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
    if(config.outputFileType == config::Xml) { // missing c++11 atm
        geip::XmlSyntaxPrinter xmlPrinter(*outputStream);
        xmlPrinter.print(entities);
    } else if(config.outputFileType == config::ExpressInstance) { // missing c++11 atm
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
