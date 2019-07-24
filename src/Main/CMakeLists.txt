
project (
    corsis
    VERSION 0.0.0
    DESCRIPTION "CORSIKA for CRAYFIS project"
    LANGUAGES CXX
    )

add_subdirectory (Utils)

add_executable (${PROJECT_NAME} main.cc)

target_link_libraries (
    ${PROJECT_NAME}
    CORSISutils
    )

install (TARGETS ${PROJECT_NAME} DESTINATION bin)
