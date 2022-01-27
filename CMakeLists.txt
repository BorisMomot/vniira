cmake_minimum_required(VERSION 3.20)
project(vniira VERSION 0.0.1 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(ProjectCommonConfigs)
include(PackageInfo)

#add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(test)