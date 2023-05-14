cmake_minimum_required(VERSION 3.24.2)
project(Minecraft)
set(CMAKE_CXX_STANDARD 20)

include(CMakeLogic.cmake)


# DIRECTORIES
set_project_directories(src src test res out)


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