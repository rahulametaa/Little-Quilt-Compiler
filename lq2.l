%{
#include<string>
#include<iostream>
#include "parse.tab.h" 
using namespace std;

%}

%option noyywrap

%%

"turn" {yylval.name=yytext; return TURN;}

"sew" {yylval.name=yytext; return SEW;}

"a"   {yylval.name=yytext; return A;}

"b"    {yylval.name=yytext; return B;}

"(" {yylval.name=yytext; return OB;}

")" {yylval.name=yytext; return CB;}

","  {yylval.name=yytext; return COMMA;}

"hdRow"  {yylval.name=yytext; return HDROW;}

"tlRow"   {yylval.name=yytext; return TLROWS;}

"hdCol"    {yylval.name=yytext; return HDCOL;}

"tlCol"   {yylval.name=yytext; return TLCOLS; }

"let"      {yylval.name=yytext; return LET;}

"fun"      {yylval.name=yytext; return FUN;}

"val"      {yylval.name=yytext; return VAL;}

"in"       {yylval.name=yytext; return IN;}

"end"      {yylval.name=yytext; return END;}

"="      {yylval.name=yytext; return ASSIGN;}
;
[a-zA-Z_][a-zA-Z0-9_]*    {yylval.name=strdup(yytext); return ID;}

.  ;

%%
