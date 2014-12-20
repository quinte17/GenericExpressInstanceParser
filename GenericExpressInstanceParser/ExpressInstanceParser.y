%skeleton "lalr1.cc"
%require "3.0"
%debug
%defines
%define api.namespace {geip}
%define parser_class_name {ExpressInstanceParser}
%define parse.error verbose
%language "C++"
%locations

%code requires{
    #include <iostream>
    #include <cstdlib>
    #include <fstream>
    #include <list>
    #include <QtGlobal>

    #include "ExpressTypes.h"
    #include "GenericExpressInstanceParser.h"

    //forward declaration
    namespace geip{
        class ExpressInstanceScanner;
    }
}

/* Defines the parameters for the yylex function that we have to define */
%lex-param { ExpressInstanceScanner& scanner }
%parse-param { ExpressInstanceScanner& scanner }

%lex-param { GenericExpressInstanceParser& parser }
%parse-param { GenericExpressInstanceParser& parser }

%code{
/* this is silly, but I can't figure out a way around */
static int yylex(geip::ExpressInstanceParser::semantic_type* yylval,
                 geip::ExpressInstanceParser::location_type* loc,
                 geip::ExpressInstanceScanner& scanner,
                 geip::GenericExpressInstanceParser& parser
                );
static void printDebug(const std::string& debug);
}

//token types
%union {
    std::string* sval;
    geip::ExpressInstance* instance;
    geip::StringInstance* string;
    geip::EnumInstance* enumInstance;
    geip::BooleanInstance* booleanInstance;
    geip::IntegerInstance* integerInstance;
    geip::RealInstance* realInstance;
    geip::AttributeInstance* attribute;
    geip::EntityInstance* entity;

    std::list<geip::ExpressInstance*>* instances;
    std::list<geip::EntityInstance*>* entities;
}

%type <instance> instance;
%type <instances> instances attributes;
%type <attribute> attribute;
%type <entity> entity;

//tokens definitions
%token END 0 "end of file"
%token NEWLINE
%token CHAR
%token L_BRACE R_BRACE
%token L_BRACKET R_BRACKET
%token <sval> NAME
%token <sval> UNKNOWN
%token ASSIGN
%token COMMA
%token <sval> STRING
%token <sval> BOOLEAN
%token <sval> INTEGER
%token <sval> REAL

//start symbol (only entities are root elements)
%start entities

%%

entities
    : entity                            {parser.addRootEntity($1);}
    | entities entity                   {parser.addRootEntity($2);}
    ;

entity
    : NAME L_BRACE R_BRACE              {$$ = new EntityInstance($1);}
    | NAME L_BRACE attributes R_BRACE   {$$ = new EntityInstance($1, $3);}
    ;

attributes
    : attribute                         {$$ = new std::list<ExpressInstance*>(); $$->push_back($1);}
    | attributes COMMA attribute        {$1->push_back($3); $$ = $1;}
    ;

attribute
    : NAME ASSIGN instance                       {$$ = new AttributeInstance($1,$3);}
    | NAME ASSIGN L_BRACKET instances R_BRACKET  {$$ = new AttributeInstance($1,$4);}
    ;

instances
    :                                   {$$ = new std::list<ExpressInstance*>();}
    | instance                          {$$ = new std::list<ExpressInstance*>(); $$->push_back($1);}
    | instances COMMA instance          {$1->push_back($3); $$ = $1;}
    ;

instance
    : NAME                              {$$ = new EnumInstance($1);}
    | STRING                            {$$ = new StringInstance($1);}
    | BOOLEAN                           {$$ = new BooleanInstance($1);}
    | INTEGER                           {$$ = new IntegerInstance($1);}
    | REAL                              {$$ = new RealInstance($1);}
    | entity                            {$$ = $1;}
    ;
%%

namespace geip{
    void ExpressInstanceParser::error(const location_type& loc, const std::string& msg)
    {
        std::cerr << "Error: " << msg << "\n";
    }
}

#include "ExpressInstanceScanner.h"
#include "ExpressInstanceParser.hpp"

static int yylex(geip::ExpressInstanceParser::semantic_type* yylval,
                 geip::ExpressInstanceParser::location_type* loc,
                 geip::ExpressInstanceScanner& scanner,
                 geip::GenericExpressInstanceParser& parser
                )
{
    Q_UNUSED(parser);
    return(scanner.yylex(yylval));
}

static void printDebug(const std::string& debug)
{
    std::cout << debug << std::endl;
}

