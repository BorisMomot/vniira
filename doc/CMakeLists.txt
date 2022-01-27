find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
  return()
endif()

# Генерируем только XML
set(DOXYGEN_GENERATE_HTML NO)
set(DOXYGEN_GENERATE_XML YES)
set(DOXYGEN_EXCLUDE_PATTERNS "*/detail/*")
set(DOXYGEN_STRIP_FROM_PATH ${PROJECT_SOURCE_DIR}/include)

doxygen_add_docs(doxygen-doc ${PROJECT_SOURCE_DIR}/include COMMENT
                 "Generating API documentation with Doxygen")

find_package(Sphinx REQUIRED)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in
               ${CMAKE_CURRENT_BINARY_DIR}/conf.py @ONLY)
add_custom_target(
  sphinx-doc ALL
  COMMAND ${SPHINX_EXECUTABLE} -b html -c ${CMAKE_CURRENT_BINARY_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generating API documentation with Sphinx"
  VERBATIM)

add_dependencies(sphinx-doc doxygen-doc)