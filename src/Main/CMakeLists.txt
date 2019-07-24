
set (
    SUBPROJECT_NAME
    corsis
    )

add_subdirectory (Utils)

add_executable (${SUBPROJECT_NAME} main.cc)

target_link_libraries (
    ${SUBPROJECT_NAME}
    CORSISutils
    )

install (TARGETS ${SUBPROJECT_NAME} DESTINATION bin)
