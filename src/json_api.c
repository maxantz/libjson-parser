#include "json.h"

extern int yyparse();
extern JsonNode* root;
extern void yy_scan_string(const char*);

JsonNode* json_parse_string(const char* json)
{
    yy_scan_string(json);

    if (yyparse() != 0)
        return NULL;

    return root;
}

