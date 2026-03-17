#include "json_ast.h"
#include <stdlib.h>
#include <string.h>

#ifndef TRUE
    #define TRUE 1
#endif
#ifndef FALSE
    #define FALSE 0
#endif

static JsonNode* json_new(JsonType type)
{
    JsonNode* n = calloc(1, sizeof(JsonNode));
    n->type = type;
    return n;
}

JsonNode* json_new_null()
{
    return json_new(JSON_NULL);
}

JsonNode* json_new_bool(int v)
{
    JsonNode* n = json_new(JSON_BOOL);
    n->boolean = v;
    return n;
}

JsonNode* json_new_integer(long v)
{
    JsonNode* n = json_new(JSON_INTEGER);
    n->integer = v;
    return n;
}

JsonNode* json_new_decimal(double v)
{
    JsonNode* n = json_new(JSON_DECIMAL);
    n->decimal = v;
    return n;
}

JsonNode* json_new_string(const char* s, size_t len)
{
    JsonNode* n = json_new(JSON_STRING);
#ifdef __HAVE_STRNDUP__
    n->string.data = strndup(s, len);
#else
    n->string.data = json_strndup(s, len);
#endif
	n->string.len = len;
    return n;
}

JsonNode* json_new_array()
{
    return json_new(JSON_ARRAY);
}

JsonNode* json_new_object()
{
    return json_new(JSON_OBJECT);
}

void json_array_add(JsonNode* array, JsonNode* value)
{
    JsonArray* a = &array->array;

    if (a->size == a->capacity) {
        a->capacity = a->capacity ? a->capacity * 2 : 4;
        a->items = realloc(a->items, a->capacity * sizeof(JsonNode*));
    }

    a->items[a->size++] = value;
}

void json_object_add(JsonNode* object, const char* key, size_t len, JsonNode* value)
{
    JsonObject* o = &object->object;

    if (o->size == o->capacity) {
        o->capacity = o->capacity ? o->capacity * 2 : 4;
        o->pairs = realloc(o->pairs, o->capacity * sizeof(JsonPair));
    }
#ifdef __HAVE_STRNDUP__
    // o->pairs[o->size].key.data = strndup(key, len);
#else
    o->pairs[o->size].key.data = json_strndup(key, len);
#endif
    o->pairs[o->size].key.len = len;
    o->pairs[o->size].value = value;

    o->size++;
}

int json_object_is_null(JsonNode* obj)
{
	if ( NULL == obj ) return FALSE;
	if ( JSON_NULL != obj->type ) return FALSE;

	return TRUE;
}

int json_object_is_bool(JsonNode* obj)
{
	if ( NULL == obj) return FALSE;
	if ( JSON_BOOL != obj->type ) return FALSE;

	return TRUE;
}

int json_object_is_integer(JsonNode* obj)
{
	if ( NULL == obj) return FALSE;
	if ( JSON_INTEGER != obj->type ) return FALSE;

	return TRUE;
}

int json_object_is_decimal(JsonNode* obj)
{
	if ( NULL == obj) return FALSE;
	if ( JSON_DECIMAL != obj->type ) return FALSE;

	return TRUE;
}

int json_object_is_string(JsonNode* obj)
{
	if ( NULL == obj) return FALSE;
	if ( JSON_STRING != obj->type ) return FALSE;

	return TRUE;
}

int json_object_is_array(JsonNode* obj)
{
	if ( NULL == obj) return FALSE;
	if ( JSON_ARRAY != obj->type ) return FALSE;

	return TRUE;
}

int json_object_is_object(JsonNode* obj)
{
	if ( NULL == obj) return FALSE;
	if ( JSON_OBJECT != obj->type ) return FALSE;

	return TRUE;
}


int json_object_have(JsonNode* obj, const char* key)
{
	if ( NULL == obj) return FALSE;
	
	
	
	return FALSE;
}

JsonNode* json_object_get(JsonNode* obj, const char* key)
{
	if ( NULL != obj)
	{
		
	}

	return NULL;
}

void json_free(JsonNode* node)
{
    if (!node) return;

    switch (node->type) {

    case JSON_STRING:
        free((char*)node->string.data);
        break;

    case JSON_ARRAY:
        for (size_t i = 0; i < node->array.size; i++)
            json_free(node->array.items[i]);
        free(node->array.items);
        break;

    case JSON_OBJECT:
        for (size_t i = 0; i < node->object.size; i++) {
            free((char*)node->object.pairs[i].key.data);
            json_free(node->object.pairs[i].value);
        }
        free(node->object.pairs);
        break;

    default:
        break;
    }

    free(node);
}

#ifndef __HAVE_STRNDUP__
char* json_strndup(const char* s, size_t len)
{
    char* out = (char*)malloc(len + 1);
    if (!out)
        return NULL;

    memcpy(out, s, len);
    out[len] = '\0';

    return out;
}
#endif

