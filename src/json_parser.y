%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_ast.h"

JsonNode* root;
int yylex();
void yyerror(const char* s);
%}

%union {
    char* string;
    long integer;
    double decimal;
    JsonNode* node;
}

%token <string> STRING
%token <integer> INTEGER
%token <decimal> DECIMAL
%token TRUE FALSE NULLTOK

%type <node> value object array members member elements

%%

json
    : value { root = $1; }
    ;

value
    : STRING { $$ = json_new_string($1, strlen($1)); free($1); }
    | INTEGER { $$ = json_new_integer($1); }
    | DECIMAL { $$ = json_new_decimal($1); }
    | TRUE   { $$ = json_new_bool(1); }
    | FALSE  { $$ = json_new_bool(0); }
    | NULLTOK{ $$ = json_new_null(); }
    | object
    | array
    ;

object
    : '{' '}' { $$ = json_new_object(); }
    | '{' members '}' { $$ = $2; }
    ;

members
    : member { $$ = $1; }
    | members ',' member {
        for(size_t i=0;i<$3->object.size;i++)
            json_object_add($1,
                $3->object.pairs[i].key.data,
                $3->object.pairs[i].key.len,
                $3->object.pairs[i].value);
        $$ = $1;
    }
    ;

member
    : STRING ':' value {
        $$ = json_new_object();
        json_object_add($$, $1, strlen($1), $3);
        free($1);
    }
    ;

array
    : '[' ']' { $$ = json_new_array(); }
    | '[' elements ']' { $$ = $2; }
    ;

elements
    : value {
        $$ = json_new_array();
        json_array_add($$, $1);
    }
    | elements ',' value {
        json_array_add($1, $3);
        $$ = $1;
    }
    ;

%%

void yyerror(const char* s)
{
    fprintf(stderr, "Parse error: %s\n", s);
}
