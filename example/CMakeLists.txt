cmake_minimum_required(VERSION 3.16)

add_executable(parser
    main.c
)

target_link_libraries(parser
    json_parser)

