cmake_minimum_required(VERSION 3.16)

project(json_parser C CXX)

enable_testing()

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(
    JsonParser
    src/json_parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/json_parser.tab.c
)

FLEX_TARGET(
    JsonLexer
    src/json_lexer.l
    ${CMAKE_CURRENT_BINARY_DIR}/json_lexer.yy.c
)

ADD_FLEX_BISON_DEPENDENCY(JsonLexer JsonParser)

include_directories(
    include
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_library(json_parser SHARED 
    src/json_api.c
    src/json_ast.c
    ${BISON_JsonParser_OUTPUTS}
    ${FLEX_JsonLexer_OUTPUTS}
)

add_subdirectory(tests)

add_subdirectory(example)

