#ifndef JSON_H
#define JSON_H

#include "json_ast.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct JsonDoc JsonDoc;

JsonNode* json_parse_string(const char* json);
void json_free(JsonNode* node);

#ifdef __cplusplus
}
#endif

#endif
