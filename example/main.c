#include <stdio.h>
#include "json.h"

int main(int argc, char** argv)
{
    const char *text = "{\"a\":1}";
    JsonNode* root = json_parse_string(text);

    if (root)
    {
        printf("parsed\n");

        json_free(root);
    }
    else
        printf("failed\n");

    return 0;
}

