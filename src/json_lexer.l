%option noyywrap

%{
#include <stdlib.h>
#include <string.h>

#include "json_ast.h"
#include "json_parser.tab.h"
%}

%%

"true"      { return TRUE; }
"false"     { return FALSE; }
"null"      { return NULLTOK; }

\"([^\\\"]|\\.)*\" {
    yylval.string = strdup(yytext+1);
    yylval.string[strlen(yylval.string)-1] = 0;
    return STRING;
}

-?[0-9]+ {
    yylval.integer = atol(yytext);
    return INTEGER;
}

-?[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)? {
    yylval.decimal = atof(yytext);
    return DECIMAL;
}

"{" return '{';
"}" return '}';
"[" return '[';
"]" return ']';
":" return ':';
"," return ',';

[ \t\n\r]+ ;

. return yytext[0];

%%
