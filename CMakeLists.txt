cmake_minimum_required(VERSION 3.21)
project(Minecraft)

set(CMAKE_CXX_STANDARD 20)

add_executable(Minecraft src/main.cpp src/window/Window.cpp src/window/Window.h src/headers/typedefs.h src/graphics/Shader.cpp src/graphics/Shader.h src/graphics/Texture.cpp src/graphics/Texture.h src/headers/includes.h src/camera/Camera.cpp src/camera/Camera.h src/time/Clock.cpp src/time/Clock.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw -lGLEW -lGL -lSOIL")