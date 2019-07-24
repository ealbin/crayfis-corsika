
set (
    UTIL_SOURCES
    input.cc
    )

set (
    UTIL_HEADERS
    input.h
    )

set (
    UTIL_NAMESPACE
    corsis/utils
    )

add_library (CORSISutils STATIC ${UTIL_SOURCES})
CORSIKA_COPY_HEADERS_TO_NAMESPACE (CORSISutils ${UTIL_NAMESPACE} ${UTIL_HEADERS})

set_target_properties (
    CORSISutils
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${UTIL_HEADERS}"
    )

target_link_libraries (
    CORSISutils
    )

target_include_directories (
    CORSISutils
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )
#PROJECT_BINARY_DIR
#CMAKE_SOURCE_DIR

install (
    TARGETS CORSISutils
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER
    DESTINATION include/${UTIL_NAMESPACE}
    )
