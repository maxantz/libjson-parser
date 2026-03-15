find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(json_tests
    test_parser.cpp
)

target_compile_definitions(json_tests PRIVATE
    -D_GNU_SOURCE
	-D__MINGW32__
)

target_compile_options(json_tests PRIVATE
    -pthread
)

target_link_libraries(json_tests
    json_parser
    GTest::gtest
    GTest::gtest_main
    Threads::Threads
)

include(GoogleTest)

gtest_discover_tests(json_tests)
