set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "VNIIRA test project")
set(CPACK_COMPONENTS_ALL major)
set(CPACK_GENERATOR RPM)
set(CPACK_RPM_PACKAGE_RELEASE 1)
set(CPACK_RPM_PACKAGE_RELEASE_DIST  ON)
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_RPM_MAIN_COMPONENT major)
set(CPACK_RPM_FILE_NAME "RPM-DEFAULT")
include (CPack)
cpack_add_component(major DESCRIPTION "Test project" )