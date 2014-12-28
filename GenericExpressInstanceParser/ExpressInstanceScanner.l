/********************************************************
 * ex1.ypp
 ********************************************************/

%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */
#include "ExpressInstanceScanner.h"
#include "ExpressInstanceParser.hpp"

/* typedef to make the returns for the tokens shorter */
typedef geip::ExpressInstanceParser::token token;

/* define yyterminate as this instead of NULL */
//#define yyterminate() return( 0 )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H
%}

/****************** Options ******************/
%option debug
%option nodefault
%option yyclass="ExpressInstanceScanner"
%option noyywrap
%option c++
/* the manual says "somewhat more optimized" */
%option batch

/* enables the use of start condition stacks */
%option stack

/*
character [a-zA-Z]
digit [0-9]
word ({character}|{digit})+
line \n
*/

character    [a-zA-Z_]
digit        [0-9]
uinteger     {digit}+
integer      [+-]?{uinteger}
real         {integer}(\.{digit}*)?
name         {character}({character}|{digit})+
lbrace       [(]
rbrace       [)]
lbracket     \[
rbracket     \]
whitespaces  [ \t]+
newline      [\n\r]
assign       [:]=
comma        [,]
string       \"(\\.|[^\\"])*\"

%%

{string}       {
                    m_yylval->sval = new std::string(yytext);
                    m_yylval->sval->erase(m_yylval->sval->begin());
                    m_yylval->sval->erase(m_yylval->sval->end() - 1);
                    return token::STRING;
               }

(TRUE|FALSE)   {
                    m_yylval->sval = new std::string(yytext);
                    return token::BOOLEAN;
               }

{integer}      {
                    m_yylval->sval = new std::string(yytext);
                    return token::INTEGER;
               }

{real}         {
                    m_yylval->sval = new std::string(yytext);
                    return token::REAL;
               }

{name}         {
                    m_yylval->sval = new std::string(yytext);
                    //std::cout << "scanner: name : " << yytext << " " << std::endl;
                    return token::NAME;
               }

{lbrace}       {
                    //std::cout << "scanner: lbrace : " << yytext << std::endl;
                    return token::L_BRACE;
               }

{rbrace}       {
                    //std::cout << "scanner: rbrace : " << yytext << std::endl;
                    return token::R_BRACE;
               }

{lbracket}     {
                    //std::cout << "scanner: lbrace : " << yytext << std::endl;
                    return token::L_BRACKET;
               }

{rbracket}     {
                    //std::cout << "scanner: rbrace : " << yytext << std::endl;
                    return token::R_BRACKET;
               }

{assign}       {
                    //std::cout << "scanner: assign : " << yytext << std::endl;
                    return token::ASSIGN;
               }

{comma}        {
                    //std::cout << "scanner: comma : " << yytext << std::endl;
                    return token::COMMA;
               }

{newline}      {
                    //we are not interested in new lines
               }

{whitespaces}  {
                    //we are not interested in white spaces...
               }

.              {
                    printf("bad input character '%s'\n", yytext);
                    exit(EXIT_FAILURE);
               }

%%
