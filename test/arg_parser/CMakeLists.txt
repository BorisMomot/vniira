add_executable(arg_parser_test arg_parser_test.cc)
target_link_libraries(arg_parser_test PRIVATE gtest_main arg_parser)
target_include_directories(arg_parser_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
gtest_discover_tests(arg_parser_test)