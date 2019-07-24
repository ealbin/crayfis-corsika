
# As additional subdirectories are added,
# update "--> Add hierarchy <--", and
# update "--> Add libraries <--" below
# Nothing else should need changing

# Name for libraries and executable
set (SUBPROJECT_NAME corsis)

# Name for CMAKE variables
set (SUBPROJECT CORSIS)

# --> Add hierarchy <--
#add_subdirectory (foo)
add_subdirectory (Utils)

# Find all source files
file (GLOB_RECURSE ${SUBPROJECT}_SOURCES "*.cc")

# Don't want/need the example provided by CORSIKA
list (
    REMOVE_ITEM
    ${SUBPROJECT}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/_demo/shower.cc
    )

add_executable (${SUBPROJECT_NAME} ${${SUBPROJECT}_SOURCES})

# --> Add libraries <--
# ${SUBPROJECT}bar
target_link_libraries (
    ${SUBPROJECT_NAME}
    ${SUBPROJECT}utils
    )

install (TARGETS ${SUBPROJECT_NAME} DESTINATION bin)
