#include <gtest/gtest.h>

extern "C" {
#include "json.h"
}

TEST(JsonParser, ParseSimpleObject)
{
    const char* text = "{\"a\":1}";

    JsonNode* root = json_parse_string(text);

    ASSERT_NE(root, nullptr);

    json_free(root);
}

TEST(JsonParser, ParseComplexObject)
{
    const char* text = "{\"o\":{\"r\":1.2,\"d\":-4,\"s\":\"some test text\",\"a\":[true, false]}}";

    JsonNode* root = json_parse_string(text);

    ASSERT_NE(root, nullptr);

    json_free(root);
}

TEST(JsonParser, ParseArray)
{
    const char* text = "[1,2,3]";

    JsonNode* root = json_parse_string(text);

    ASSERT_NE(root, nullptr);

    json_free(root);
}

TEST(JsonParser, ParseInvalidJson)
{
    const char* text = "{";

    JsonNode* root = json_parse_string(text);

    ASSERT_EQ(root, nullptr);
}

