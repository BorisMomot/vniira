include(CTest)
include(FetchGTest)
include(GoogleTest)

add_subdirectory(arg_parser)
add_subdirectory(buffer_processor)
add_subdirectory(result_accumulator)
add_subdirectory(str_number)
add_subdirectory(thread_pool)

enable_testing()
# Интеграционные тесты
set(TEST_PROGRAM ${CMAKE_BINARY_DIR}/src/${PROJECT_NAME})
set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_numbers)
#-----------------------------------------------------------------------------------------------------------------------
# 1. Простой тест из небольшого числа единиц
add_test(NAME numbers_small_and_simple COMMAND ${TEST_PROGRAM} -f ${TEST_DATA_DIR}/numbers_small_and_simple.txt)
set_tests_properties(numbers_small_and_simple PROPERTIES
        PASS_REGULAR_EXPRESSION "totalSum: 23 totalSubtract: -21 totalXor: 1")
#-----------------------------------------------------------------------------------------------------------------------
# 2. Последовательность из негативных чисел с переносами
add_test(NAME numbers_small_and_negative COMMAND ${TEST_PROGRAM} -f ${TEST_DATA_DIR}/numbers_small_and_negative.txt)
set_tests_properties(numbers_small_and_negative PROPERTIES
        PASS_REGULAR_EXPRESSION "totalSum: -1800 totalSubtract: 2000 totalXor: -8")
#-----------------------------------------------------------------------------------------------------------------------
# 3. Большие числа
add_test(NAME numbers_long COMMAND ${TEST_PROGRAM} -f ${TEST_DATA_DIR}/numbers_long.txt)
set_tests_properties(numbers_long PROPERTIES
        PASS_REGULAR_EXPRESSION "totalSum: 3689348814741911228 totalSubtract: -1844674407370955614 totalXor: 0")
#-----------------------------------------------------------------------------------------------------------------------
# 4. Пример из задания
add_test(NAME numbers COMMAND ${TEST_PROGRAM} -f ${TEST_DATA_DIR}/numbers.txt)
set_tests_properties(numbers PROPERTIES
        PASS_REGULAR_EXPRESSION "totalSum: 2758646078950 totalSubtract: -2751738516022 totalXor: 240293890")
#-----------------------------------------------------------------------------------------------------------------------
# 5. Пример из задания с маленьким буфером
add_test(NAME numbers_small_buffer COMMAND ${TEST_PROGRAM} -b 100 -f ${TEST_DATA_DIR}/numbers.txt)
set_tests_properties(numbers_small_buffer PROPERTIES
        PASS_REGULAR_EXPRESSION "totalSum: 2758646078950 totalSubtract: -2751738516022 totalXor: 240293890")