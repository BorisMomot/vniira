add_subdirectory(arg_parser)
add_subdirectory(buffer_pool)
add_subdirectory(buffer_processor)
add_subdirectory(str_number)
add_subdirectory(thread_pool)

add_executable(vniira main.cpp)
target_link_libraries(vniira pthread str_number buffer_pool thread_pool arg_parser buffer_processor)

install(TARGETS vniira RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT major)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.md DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT major)