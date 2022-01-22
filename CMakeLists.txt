cmake_minimum_required(VERSION 3.21)
project(Minecraft)

set(CMAKE_CXX_STANDARD 20)

add_executable(Minecraft src/main.cpp src/window/Window.cpp src/window/Window.h src/headers/typedefs.h src/graphics/Shader.cpp src/graphics/Shader.h src/graphics/Texture2D.cpp src/graphics/Texture2D.h src/headers/includes.h src/camera/Camera.cpp src/camera/Camera.h src/time/Clock.cpp src/time/Clock.h src/exception/MessageException.cpp src/exception/MessageException.h src/graphics/Mesh.cpp src/graphics/Mesh.h src/voxel/Voxel.cpp src/voxel/Voxel.h src/voxel/Chunk.cpp src/voxel/Chunk.h src/graphics/VoxelsRenderer.cpp src/graphics/VoxelsRenderer.h src/voxel/ChunkHeap.cpp src/voxel/ChunkHeap.h src/graphics/MeshHeap.cpp src/graphics/MeshHeap.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw -lGLEW -lGL -lSOIL")