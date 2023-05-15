cmake_minimum_required(VERSION 3.24.2)



# Link libraries to TARGET by their names or files
function(auto_target_link_libraries TARGET)

    foreach(LIBRARY IN ITEMS ${ARGN})

        set(${LIBRARY}_LINKED FALSE)

        if(EXISTS ${LIBRARY})
            # checking absolute path
            target_link_libraries(${TARGET} ${LIBRARY})
            set(${LIBRARY}_LINKED TRUE)
        else()
            # checking if pkg-config can find it
            find_package(PkgConfig)
            pkg_check_modules(LIB_${LIBRARY} QUIET ${LIBRARY})
            if(DEFINED LIB_${LIBRARY}_LIBRARIES)
                target_link_libraries(${TARGET} ${LIB_${LIBRARY}_LIBRARIES})
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
                target_link_libraries(${TARGET} ${LIB_DIR}/${LIBRARY})
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/${LIBRARY}.a)
                target_link_libraries(${TARGET} ${LIB_DIR}/${LIBRARY}.a)
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/${LIBRARY}.so)
                target_link_libraries(${TARGET} ${LIB_DIR}/${LIBRARY}.so)
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/lib${LIBRARY})
                target_link_libraries(${TARGET} ${LIB_DIR}/lib${LIBRARY})
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/lib${LIBRARY}.a)
                target_link_libraries(${TARGET} ${LIB_DIR}/lib${LIBRARY}.a)
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/lib${LIBRARY}.so)
                target_link_libraries(${TARGET} ${LIB_DIR}/lib${LIBRARY}.so)
                set(${LIBRARY}_LINKED TRUE)
            endif()
        endforeach()

        # library not found
        if(NOT ${${LIBRARY}_LINKED} STREQUAL TRUE)
            message(FATAL_ERROR "Cannot find library ${LIBRARY}.")
        endif()
    endforeach()
endfunction()



# Set include, source, test, resource and out directories
# !!! CMAKE_ARCHIVE_OUTPUT_DIRECTORY must be set before this function !!!
function(set_project_directories INCLUDE_DIR SOURCE_DIR TEST_DIR RESOURCE_DIR LIB_DIR OUT_DIR)

    set(INCLUDE_DIR ${INCLUDE_DIR} PARENT_SCOPE)
    set(SOURCE_DIR ${SOURCE_DIR} PARENT_SCOPE)
    set(TEST_DIR ${TEST_DIR} PARENT_SCOPE)
    set(RESOURCE_DIR ${RESOURCE_DIR} PARENT_SCOPE)
    set(LIB_DIR ${LIB_DIR} PARENT_SCOPE)

    file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS ${INCLUDE_DIR}/*.h ${INCLUDE_DIR}/*.hh ${INCLUDE_DIR}/*.hpp)
    file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.cc)
    file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS ${TEST_DIR}/*.cpp ${TEST_DIR}/*.cc ${TEST_DIR}/*.h ${TEST_DIR}/*.hh ${TEST_DIR}/*.hpp)
    file(GLOB_RECURSE RESOURCE_FILES CONFIGURE_DEPENDS ${RESOURCE_DIR}/*)
    file(GLOB_RECURSE LIB_FILES CONFIGURE_DEPENDS ${LIB_DIR}/*)

    set(HEADERS ${HEADERS} PARENT_SCOPE)
    set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
    set(TEST_FILES ${TEST_FILES} PARENT_SCOPE)
    set(RESOURCE_FILES ${RESOURCE_FILES} PARENT_SCOPE)

    include_directories(${INCLUDE_DIR})

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

endfunction()