#ifndef JSON_AST_H
#define JSON_AST_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    JSON_NULL,
    JSON_BOOL,
    JSON_INTEGER,
    JSON_DECIMAL,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;

typedef struct JsonNode JsonNode;

typedef struct {
    const char *data;
    size_t len;
} JsonString;

typedef struct {
    JsonNode **items;
    size_t size;
    size_t capacity;
} JsonArray;

typedef struct {
    JsonString key;
    JsonNode *value;
} JsonPair;

typedef struct {
    JsonPair *pairs;
    size_t size;
    size_t capacity;
} JsonObject;

struct JsonNode {
    JsonType type;
    union {
        long integer;
        double decimal;
        uint8_t boolean;
        JsonString string;
        JsonArray array;
        JsonObject object;
    };
};

JsonNode* json_new_null();
JsonNode* json_new_bool(int v);
JsonNode* json_new_integer(long v);
JsonNode* json_new_decimal(double v);
JsonNode* json_new_string(const char* s, size_t len);
JsonNode* json_new_array();
JsonNode* json_new_object();

void json_array_add(JsonNode* array, JsonNode* value);
void json_object_add(JsonNode* object, const char* key, size_t len, JsonNode* value);

int json_object_is_null(JsonNode* obj);
int json_object_is_bool(JsonNode* obj);
int json_object_is_integer(JsonNode* obj);
int json_object_is_decimal(JsonNode* obj);
int json_object_is_string(JsonNode* obj);
int json_object_is_array(JsonNode* obj);
int json_object_is_object(JsonNode* obj);

int json_object_have(JsonNode* obj, const char* key);
JsonNode* json_object_get(JsonNode* obj, const char* key);


void json_free(JsonNode* node);

#ifndef __HAVE_STRNDUP__
static char* json_strndup(const char* s, size_t len);
#endif

#endif

