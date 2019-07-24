
# This works for any subdirectory, find/replace "utils" to foobar

add_library (${SUBPROJECT}utils INTERFACE)

# namespace of library -> location of header files
set (${SUBPROJECT}utils_NAMESPACE ${SUBPROJECT_NAME}/utils)

# header files of this library
file (GLOB ${SUBPROJECT}utils_HEADERS "*.h")
CORSIKA_COPY_HEADERS_TO_NAMESPACE (
    ${SUBPROJECT}utils
    ${${SUBPROJECT}utils_NAMESPACE}
    ${${SUBPROJECT}utils_HEADERS}
    )

# include directive for upstream code
target_include_directories (
    ${SUBPROJECT}utils
    INTERFACE
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include/>
    )

# install library
install (
    FILES ${${SUBPROJECT}utils_HEADERS}
    DESTINATION include/${${SUBPROJECT}utils_NAMESPACE}
    )
