cmake_minimum_required(VERSION 3.24.2)



# Link libraries to TARGET by their names or files
function(auto_target_link_libraries TARGET)

    find_package(PkgConfig)

    foreach(LIBRARY IN ITEMS ${ARGN})

        set(${LIBRARY}_LINKED FALSE)

        if(EXISTS ${LIBRARY})
            target_link_libraries(${TARGET} ${LIBRARY})
            set(${LIBRARY}_LINKED TRUE)
        else()
            pkg_check_modules(LIB_${LIBRARY} QUIET ${LIBRARY})
            if(DEFINED LIB_${LIBRARY}_LIBRARIES)
                target_link_libraries(${TARGET} ${LIB_${LIBRARY}_LIBRARIES})
                set(${LIBRARY}_LINKED TRUE)
            endif()
        endif()

        if(${${LIBRARY}_LINKED} STREQUAL TRUE)
            continue()
        endif()

        foreach(LIB_DIR IN ITEMS ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})
            if(EXISTS ${LIB_DIR}/${LIBRARY})
                target_link_libraries(${TARGET} ${LIB_DIR}/${LIBRARY})
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/${LIBRARY}.a)
                target_link_libraries(${TARGET} ${LIB_DIR}/${LIBRARY}.a)
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/${LIBRARY}.so)
                target_link_libraries(${TARGET} ${LIB_DIR}/${LIBRARY}.so)
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/lib${LIBRARY}.a)
                target_link_libraries(${TARGET} ${LIB_DIR}/lib${LIBRARY}.a)
                set(${LIBRARY}_LINKED TRUE)
            elseif(EXISTS ${LIB_DIR}/lib${LIBRARY}.so)
                target_link_libraries(${TARGET} ${LIB_DIR}/lib${LIBRARY}.so)
                set(${LIBRARY}_LINKED TRUE)
            endif()
        endforeach()

        if(NOT ${${LIBRARY}_LINKED} STREQUAL TRUE)
            message(FATAL_ERROR "Cannot find library ${LIBRARY}.")
        endif()
    endforeach()
endfunction()



# Set include, source, test, resource and out directories
function(set_project_directories INCLUDE_DIR SOURCE_DIR TEST_DIR RESOURCE_DIR OUT_DIR)

    set(INCLUDE_DIR ${INCLUDE_DIR} PARENT_SCOPE)
    set(SOURCE_DIR ${SOURCE_DIR} PARENT_SCOPE)
    set(TEST_DIR ${TEST_DIR} PARENT_SCOPE)
    set(RESOURCE_DIR ${RESOURCE_DIR} PARENT_SCOPE)

    file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS ${INCLUDE_DIR}/*.h ${INCLUDE_DIR}/*.hh ${INCLUDE_DIR}/*.hpp)
    file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.cc)
    file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS ${TEST_DIR}/*.cpp ${TEST_DIR}/*.cc ${TEST_DIR}/*.h ${TEST_DIR}/*.hh ${TEST_DIR}/*.hpp)
    file(GLOB_RECURSE RESOURCE_FILES CONFIGURE_DEPENDS ${RESOURCE_DIR}/*)

    set(HEADERS ${HEADERS} PARENT_SCOPE)
    set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
    set(TEST_FILES ${TEST_FILES} PARENT_SCOPE)
    set(RESOURCE_FILES ${RESOURCE_FILES} PARENT_SCOPE)

    include_directories(${INCLUDE_DIR})

    set(OUT_DIR ${OUT_DIR} PARENT_SCOPE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR} PARENT_SCOPE)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR} PARENT_SCOPE)
    execute_process(COMMAND mkdir -p ${PROJECT_BINARY_DIR}/${OUT_DIR}/)

endfunction()