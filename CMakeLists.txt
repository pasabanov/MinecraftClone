cmake_minimum_required(VERSION 3.21)
project(Minecraft)

set(CMAKE_CXX_STANDARD 20)

add_executable(Minecraft src/main.cpp src/engine/window/Window.cpp src/engine/window/Window.h src/headers/typedefs.h src/engine/graphics/Shader.cpp src/engine/graphics/Shader.h src/engine/graphics/Texture2D.cpp src/engine/graphics/Texture2D.h src/headers/includes.h src/engine/camera/Camera.cpp src/engine/camera/Camera.h src/engine/time/Clock.cpp src/engine/time/Clock.h src/engine/exception/MessageException.cpp src/engine/exception/MessageException.h src/engine/graphics/Mesh.cpp src/engine/graphics/Mesh.h src/engine/voxel/Voxel.cpp src/engine/voxel/Voxel.h src/engine/voxel/Chunk.cpp src/engine/voxel/Chunk.h src/engine/graphics/VoxelsRenderer.cpp src/engine/graphics/VoxelsRenderer.h src/engine/voxel/ChunkHeap.cpp src/engine/voxel/ChunkHeap.h src/engine/graphics/MeshHeap.cpp src/engine/graphics/MeshHeap.h src/engine/view/View.h src/game/world/VoxelWorld.cpp src/game/world/VoxelWorld.h src/engine/view/View.cpp src/engine/window/Events.cpp src/engine/window/Events.h src/engine/window/Key.h src/app/Application.cpp src/app/Application.h src/engine/graphics/LineBatch.cpp src/engine/graphics/LineBatch.h src/engine/light/LightMap.cpp src/engine/light/LightMap.h src/engine/light/LightSolver.cpp src/engine/light/LightSolver.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw -lGLEW -lGL -lSOIL")