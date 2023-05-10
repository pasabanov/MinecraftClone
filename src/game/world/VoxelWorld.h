#ifndef MINECRAFT_VOXELWORLD_H
#define MINECRAFT_VOXELWORLD_H

#include <headers/includes.h>

#include <engine/view/View.h>
#include <engine/graphics/VoxelsRenderer.h>
#include <engine/graphics/Shader.h>
#include <engine/camera/Camera.h>
#include <engine/graphics/Texture2D.h>
#include <engine/graphics/LineBatch.h>
#include <engine/light/LightSolver.h>


class VoxelWorld : public View {

    inline static const float crosshair_vertices[] = {
            -0.01, -0.01,
            0.01, 0.01,

            -0.01, 0.01,
            0.01, -0.01
    };
    inline static const int crosshair_attrs[] = { 2, 0 };

    VoxelsRenderer mRenderer;
    ChunkHeap mChunks;
    MeshHeap mMeshes;

    LightSolver mSolverR;
    LightSolver mSolverG;
    LightSolver mSolverB;
    LightSolver mSolverS;

    Shader mTextureShader;
    Texture2D mTexture;

    Shader mCrosshairShader;
    Mesh mCrosshairMesh;

    Shader mLineShader;
    LineBatch mHighlighting;

    Camera mCamera;

    void initializeLight();

public:

    VoxelWorld(int width, int height, int worldWidth, int worldHeight, int worldLength);

    void onViewSizeChanged(int width, int height) override;

    void applyEvents(const Events &events, float elapsedTime) override;

    void update() override;

    void draw() const override;

    void save(const std::string& filename) const;
    void load(const std::string& filename);
};

#endif //MINECRAFT_VOXELWORLD_H
