cmake_minimum_required(VERSION 3.21)
project(Minecraft)

set(CMAKE_CXX_STANDARD 20)

add_executable(Minecraft main.cpp window/Window.cpp window/Window.h window/EventsHandler.cpp window/EventsHandler.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw -lglut -lGLEW -lGL")