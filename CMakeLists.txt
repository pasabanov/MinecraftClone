cmake_minimum_required(VERSION 3.24.2)
project(Minecraft)
set(CMAKE_CXX_STANDARD 20)



# Functions for library linking
function(auto_link_libraries [...])
    find_package(PkgConfig)
    foreach(i RANGE 0 ${ARGC}-1)
        pkg_check_modules(LIB_${ARGV${i}} REQUIRED ${ARGV${i}})
        target_link_libraries(${CMAKE_PROJECT_NAME} ${LIB_${ARGV${i}}_LIBRARIES})
    endforeach()
endfunction()

function(link_library INCLUDE_DIRECTORY LIBRARY_FILE)
    include_directories(${INCLUDE_DIRECTORY})
    set(LIB_${LIBRARY_FILE} ${LIBRARY_FILE})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${LIB_${LIBRARY_FILE}})
endfunction()



# DIRECTORIES
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(RESOURCE_DIR ${PROJECT_SOURCE_DIR}/res)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY out)



# FILES
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS ${INCLUDE_DIR}/*.h ${INCLUDE_DIR}/*.hh ${INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.cc)
file(GLOB_RECURSE RESOURCE_FILES CONFIGURE_DEPENDS ${RESOURCE_DIR}/*)



# Include directory of project
include_directories(${INCLUDE_DIR})



# EXECUTABLE
add_executable(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCE_FILES})



# LIBRARIES
auto_link_libraries(gl opengl glfw3 glew)

link_library(/usr/include/SOIL /usr/lib/libSOIL.so)



# Copy resources
# create symbolic link
execute_process(COMMAND ln -sfT ${PROJECT_SOURCE_DIR}/res/ ${PROJECT_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res)
# actual copy
#execute_process(COMMAND cp -r ${PROJECT_SOURCE_DIR}/res/ ${PROJECT_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY})