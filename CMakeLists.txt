# MinecraftClone
# Copyright (C) © 2022  Petr Alexandrovich Sabanov
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.24.2)
project(MinecraftClone)
set(CMAKE_CXX_STANDARD 20)

include(Functions.cmake)


# DIRECTORIES
set_project_directories(src src test res include lib out)


# EXECUTABLE
set(EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})
set(EXECUTABLE_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME})
add_executable(${EXECUTABLE_NAME} ${HEADER_FILES} ${SOURCE_FILES})


# PROFILES
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(${EXECUTABLE_NAME} PRIVATE DEBUG _DEBUG DEBUG_MODE)
	target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -O0 -g3)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_definitions(${EXECUTABLE_NAME} PRIVATE RELEASE _RELEASE RELEASE_MODE NDEBUG NO_DEBUG)
	target_compile_options(${EXECUTABLE_NAME} PRIVATE -O3 -flto -s -Wl,-s -Wl,--gc-sections)
	add_strip_command(${EXECUTABLE_NAME} ${EXECUTABLE_PATH} OPTIONS -s)
elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	target_compile_definitions(${EXECUTABLE_NAME} PRIVATE RELEASE _RELEASE RELEASE_MODE NDEBUG NO_DEBUG RELWITHDEBINFO)
	target_compile_options(${EXECUTABLE_NAME} PRIVATE -O2 -flto -g3)
elseif (CMAKE_BUILD_TYPE STREQUAL "MinSize" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
	target_compile_definitions(${EXECUTABLE_NAME} PRIVATE RELEASE _RELEASE RELEASE_MODE NDEBUG NO_DEBUG MINSIZE MINSIZEREL)
	target_compile_options(${EXECUTABLE_NAME} PRIVATE -Os -flto -s -Wl,-s -Wl,--gc-sections)
	add_strip_command(${EXECUTABLE_NAME} ${EXECUTABLE_PATH} OPTIONS -s)
else()
	# do nothing
endif()


# LIBRARIES
find_libraries(LIBRARIES REQUIRED gl opengl glfw3 glew SOIL)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARIES})


# Copy resources
# create symbolic link
#execute_process(COMMAND ln -sfT ${PROJECT_SOURCE_DIR}/${RESOURCE_DIR}/ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${RESOURCE_DIR})
# actual copy
execute_process(COMMAND cp -r ${PROJECT_SOURCE_DIR}/${RESOURCE_DIR}/ ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})