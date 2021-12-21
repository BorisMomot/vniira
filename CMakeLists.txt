cmake_minimum_required(VERSION 3.20)
project(vniira)

set(CMAKE_CXX_STANDARD 17)

add_executable(vniira main.cpp StrNumber.h StrNumber.cc ThreadPool.h ThreadPool.cc ArgParser.h ResultAccumulator.h BufferProcessors.h)
target_link_libraries(vniira pthread)

include (GNUInstallDirs)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "VNIIRA test project")
set(CPACK_COMPONENTS_ALL major)
set(CPACK_GENERATOR RPM)
set(CPACK_RPM_PACKAGE_RELEASE 1)
set(CPACK_RPM_PACKAGE_RELEASE_DIST  ON)
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_RPM_MAIN_COMPONENT major)
set(CPACK_RPM_FILE_NAME "RPM-DEFAULT")

include (CPack)

install(TARGETS vniira RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT major)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.md DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT major)
cpack_add_component(major DESCRIPTION "Test project" )