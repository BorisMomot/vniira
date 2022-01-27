add_library(strNumber StrNumber.cc)
target_link_libraries(strNumber pthread)
target_include_directories(strNumber PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(vniira main.cpp ThreadPool.cc)
target_link_libraries(vniira pthread strNumber)
target_include_directories(vniira PUBLIC ${PROJECT_SOURCE_DIR}/include)

install(TARGETS vniira RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT major)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.md DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT major)