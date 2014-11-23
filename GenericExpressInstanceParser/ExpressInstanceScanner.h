#ifndef EXPRESS_INSTANCE_SCANNER_H
#define EXPRESS_INSTANCE_SCANNER_H

#if ! defined(yyFlexLexerOnce)
    #include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL int geip::ExpressInstanceScanner::yylex()

#include "ExpressInstanceParser.hpp"

namespace geip{

class ExpressInstanceScanner : public yyFlexLexer
{
public:
    ExpressInstanceScanner(std::istream *in)
        : yyFlexLexer(in)
        , m_yylval(NULL)
    {

    }

//    int scan(void){
//        wordCount = 0;

//        yylex();
//        return wordCount;
//    }

    int yylex(geip::ExpressInstanceParser::semantic_type* _yylval)
    {
        m_yylval = _yylval;
        return yylex();
    }

private:
    virtual int yylex(); //disable it
    /* yyval ptr */
    geip::ExpressInstanceParser::semantic_type* m_yylval;
};

} //geip

#endif // EXPRESS_INSTANCE_SCANNER_H
