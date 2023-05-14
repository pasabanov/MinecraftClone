cmake_minimum_required(VERSION 3.24.2)
project(Minecraft)
set(CMAKE_CXX_STANDARD 20)


# INCLUDES
include(LibraryLinking.cmake)



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
set(EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${HEADERS} ${SOURCE_FILES})



# LIBRARIES
auto_target_link_libraries(${EXECUTABLE_NAME} gl opengl glfw3 glew SOIL)



# Copy resources
# create symbolic link
execute_process(COMMAND ln -sfT ${PROJECT_SOURCE_DIR}/res/ ${PROJECT_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res)
# actual copy
#execute_process(COMMAND cp -r ${PROJECT_SOURCE_DIR}/res/ ${PROJECT_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY})