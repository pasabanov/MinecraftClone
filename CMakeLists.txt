cmake_minimum_required(VERSION 3.24.2)
project(Minecraft)
set(CMAKE_CXX_STANDARD 20)

include(CMakeLogic.cmake)


# DIRECTORIES
set_project_directories(src src test res lib out)


# EXECUTABLE
set(EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${HEADERS} ${SOURCE_FILES})


# LIBRARIES
find_libraries(LIBRARIES gl opengl glfw3 glew SOIL)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARIES})


# Copy resources
# create symbolic link
execute_process(COMMAND ln -sfT ${PROJECT_SOURCE_DIR}/${RESOURCE_DIR}/ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${RESOURCE_DIR})
# actual copy
#execute_process(COMMAND cp -r ${PROJECT_SOURCE_DIR}/${RESOURCE_DIR}/ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})