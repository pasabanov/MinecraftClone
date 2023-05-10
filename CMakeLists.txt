cmake_minimum_required(VERSION 3.24.2)
project(Minecraft)
set(CMAKE_CXX_STANDARD 20)

include_directories(src)


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


# SOURCE FILES

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp src/*.cc src/*.h src/*.hh src/*.hpp)


# EXECUTABLE

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})


# LIBRARIES

auto_link_libraries(gl opengl glfw3 glew)

link_library(/usr/include/SOIL /usr/lib/libSOIL.so)