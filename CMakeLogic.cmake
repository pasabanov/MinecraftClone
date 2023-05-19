cmake_minimum_required(VERSION 3.24.2)



function(find_libraries OUT_VAR)

    unset(LIBRARIES_LIST)

    foreach(LIBRARY IN ITEMS ${ARGN})

        set(${LIBRARY}_LINKED FALSE)

        if(EXISTS ${LIBRARY})
            # checking absolute or relative to project path
            list(APPEND LIBRARIES_LIST ${LIBRARY})
            set(${LIBRARY}_LINKED TRUE)
        else()
            # checking if pkg-config can find it
            find_package(PkgConfig)
            pkg_check_modules(LIB_${LIBRARY} QUIET ${LIBRARY})
            if(DEFINED LIB_${LIBRARY}_LIBRARIES)
                list(APPEND LIBRARIES_LIST ${LIB_${LIBRARY}_LIBRARIES})
                set(${LIBRARY}_LINKED TRUE)
            endif()
        endif()

        # library is found, no need to search further
        if(${${LIBRARY}_LINKED} STREQUAL TRUE)
            continue()
        endif()

        # directories to search
        set(LIBRARY_SEARCH_DIRECTORIES ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})
        # searching in project directory too
        list(APPEND LIBRARY_SEARCH_DIRECTORIES
                ${PROJECT_SOURCE_DIR}
                ${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/libs
                ${PROJECT_SOURCE_DIR}/library ${PROJECT_SOURCE_DIR}/libraries
                ${PROJECT_SOURCE_DIR}/l ${PROJECT_SOURCE_DIR}/L
                ${LIB_DIR} ${LIBS_DIR} ${LIBRARY_DIR} ${LIBRARIES_DIR}
                ${LIB_DIRECTORY} ${LIBS_DIRECTORY} ${LIBRARY_DIRECTORY} ${LIBRARIES_DIRECTORY}
                ${LIB_FOLDER} ${LIBS_FOLDER} ${LIBRARY_FOLDER} ${LIBRARIES_FOLDER})

        # searching
        foreach(LIB_DIR IN ITEMS ${LIBRARY_SEARCH_DIRECTORIES})

            if(EXISTS ${LIB_DIR}/${LIBRARY})
                list(APPEND LIBRARIES_LIST ${LIB_DIR}/${LIBRARY})
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/${LIBRARY}.a)
                list(APPEND LIBRARIES_LIST ${LIB_DIR}/${LIBRARY}.a)
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/${LIBRARY}.so)
                list(APPEND LIBRARIES_LIST ${LIB_DIR}/${LIBRARY}.so)
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/lib${LIBRARY})
                list(APPEND LIBRARIES_LIST ${LIB_DIR}/lib${LIBRARY})
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/lib${LIBRARY}.a)
                list(APPEND LIBRARIES_LIST ${LIB_DIR}/lib${LIBRARY}.a)
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/lib${LIBRARY}.so)
                list(APPEND LIBRARIES_LIST ${LIB_DIR}/lib${LIBRARY}.so)
                set(${LIBRARY}_LINKED TRUE)
            endif()

            # library is found, no need to search further
            if(${${LIBRARY}_LINKED} STREQUAL TRUE)
                break()
            endif()
        endforeach()

        # library not found
        if(NOT ${${LIBRARY}_LINKED} STREQUAL TRUE)
            message(FATAL_ERROR "Cannot find library ${LIBRARY}.")
        endif()
    endforeach()

    set(${OUT_VAR} ${LIBRARIES_LIST} PARENT_SCOPE)
endfunction()



# Set include, source, test, resource and out directories.
# !!! CMAKE_ARCHIVE_OUTPUT_DIRECTORY must be set before this function !!!
# Creates variables in the parent scope:
#       HEADER_DIR,     HEADER_FILES    - directory with header files, corresponding files list
#       SOURCE_DIR,     SOURCE_FILES    - directory with .cpp (.cc) files, corresponding files list
#       TEST_DIR,       TEST_FILES      - directory with test files, corresponding files list
#       RESOURCE_DIR,   RESOURCE_FILES  - directory with resource files, corresponding files list
#       INCLUDE_DIR,    INCLUDE_FILES   - directory with headers that this project includes, corresponding files list
#       LIB_DIR,        LIB_FILES       - directory with library files, corresponding files list
#       OUT_DIR                         - directory with compiler output
# OUT_DIR is used for all output directories of the compiler
function(set_project_directories HEADER_DIR SOURCE_DIR TEST_DIR RESOURCE_DIR INCLUDE_DIR LIB_DIR OUT_DIR)

    include_directories(${HEADER_DIR} ${INCLUDE_DIR})

    # index files
    if(NOT HEADER_DIR STREQUAL "")
        file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
                ${HEADER_DIR}/*.h ${HEADER_DIR}/*.hh ${HEADER_DIR}/*.hpp ${HEADER_DIR}/*.hxx)
    endif()
    if(NOT SOURCE_DIR STREQUAL "")
        file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
                ${SOURCE_DIR}/*.c ${SOURCE_DIR}/*.cc ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.cxx)
    endif()
    if(NOT TEST_DIR STREQUAL "")
        file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS
                ${TEST_DIR}/*.c ${TEST_DIR}/*.cc ${TEST_DIR}/*.cpp ${TEST_DIR}/*.cxx
                ${TEST_DIR}/*.h ${TEST_DIR}/*.hh ${TEST_DIR}/*.hpp ${TEST_DIR}/*.hxx)
    endif()
    if(NOT RESOURCE_DIR STREQUAL "")
        file(GLOB_RECURSE RESOURCE_FILES CONFIGURE_DEPENDS
                ${RESOURCE_DIR}/*)
    endif()
    if(NOT INCLUDE_DIR STREQUAL "")
        file(GLOB_RECURSE INCLUDE_FILES CONFIGURE_DEPENDS
                ${INCLUDE_DIR}/*.h ${INCLUDE_DIR}/*.hh ${INCLUDE_DIR}/*.hpp ${INCLUDE_DIR}/*.hxx)
    endif()
    if(NOT LIB_DIR STREQUAL "")
        file(GLOB_RECURSE LIB_FILES CONFIGURE_DEPENDS
                ${LIB_DIR}/*.a ${LIB_DIR}/*.so)
    endif()

    # set out directory and create it
    set(OUT_DIR ${OUT_DIR} PARENT_SCOPE)
    if(IS_ABSOLUTE ${OUT_DIR})
        set(ABSOLUTE_OUT_DIR ${OUT_DIR})
    else()
        set(ABSOLUTE_OUT_DIR ${PROJECT_BINARY_DIR}/${OUT_DIR})
    endif()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ABSOLUTE_OUT_DIR} PARENT_SCOPE)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ABSOLUTE_OUT_DIR} PARENT_SCOPE)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ABSOLUTE_OUT_DIR} PARENT_SCOPE)
    set(CMAKE_PDB_OUTPUT_DIRECTORY ${ABSOLUTE_OUT_DIR} PARENT_SCOPE)
    set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${ABSOLUTE_OUT_DIR} PARENT_SCOPE)
    execute_process(COMMAND mkdir -p ${ABSOLUTE_OUT_DIR}/)

    # set variables in the parent scope
    set(HEADER_DIR ${HEADER_DIR} PARENT_SCOPE)
    set(SOURCE_DIR ${SOURCE_DIR} PARENT_SCOPE)
    set(TEST_DIR ${TEST_DIR} PARENT_SCOPE)
    set(RESOURCE_DIR ${RESOURCE_DIR} PARENT_SCOPE)
    set(INCLUDE_DIR ${INCLUDE_DIR} PARENT_SCOPE)
    set(LIB_DIR ${LIB_DIR} PARENT_SCOPE)

    set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
    set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
    set(TEST_FILES ${TEST_FILES} PARENT_SCOPE)
    set(RESOURCE_FILES ${RESOURCE_FILES} PARENT_SCOPE)
    set(INCLUDE_FILES ${INCLUDE_FILES} PARENT_SCOPE)
    set(LIB_FILES ${LIB_FILES} PARENT_SCOPE)

endfunction()