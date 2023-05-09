#include "VoxelWorld.h"



void VoxelWorld::initializeLight() {
    
    for (int y = 0; y < mChunks.getHeight()*Chunk::HEIGHT; ++y) {
        for (int z = 0; z < mChunks.getLength()*Chunk::LENGTH; ++z) {
            for (int x = 0; x < mChunks.getWidth()*Chunk::WIDTH; ++x) {
                Voxel* vox = &mChunks.getVoxelGlobal(x, y, z);
                if (vox->getId() == 3) {
                    mSolverR.add(x, y, z, 0xF);
                    mSolverG.add(x, y, z, 0xF);
                    mSolverB.add(x, y, z, 0xF);
                }
            }
        }
    }

    for (int z = 0; z < mChunks.getLength()*Chunk::LENGTH; ++z) {
        for (int x = 0; x < mChunks.getWidth()*Chunk::WIDTH; ++x) {
            for (int y = mChunks.getHeight()*Chunk::HEIGHT-1; y >= 0; --y) {
                Voxel* vox = &mChunks.getVoxelGlobal(x, y, z);
                if (vox->getId() != 0)
                    break;
                mChunks.getChunkPtrByVoxel(x, y, z)->setLight(x % Chunk::WIDTH, y % Chunk::HEIGHT, z % Chunk::LENGTH, 3, 0xF);
            }
        }
    }

    for (int z = 0; z < mChunks.getLength()*Chunk::LENGTH; ++z) {
        for (int x = 0; x < mChunks.getWidth()*Chunk::WIDTH; ++x) {
            for (int y = mChunks.getHeight()*Chunk::HEIGHT-1; y >= 0; --y) {
                Voxel* vox = &mChunks.getVoxelGlobal(x, y, z);
                if (vox->getId() != 0)
                    break;
                if (
                        mChunks.getLight(x - 1, y, z, 3) == 0
                        || mChunks.getLight(x + 1, y, z, 3) == 0
                        || mChunks.getLight(x, y - 1, z, 3) == 0
                        || mChunks.getLight(x, y + 1, z, 3) == 0
                        || mChunks.getLight(x, y, z - 1, 3) == 0
                        || mChunks.getLight(x, y, z + 1, 3) == 0
                        ) {
                    mSolverS.add(x, y, z);
                }
                mChunks.getChunkPtrByVoxel(x, y, z)->setLight(x % Chunk::WIDTH, y % Chunk::HEIGHT, z % Chunk::LENGTH, 3, 0xF);
            }
        }
    }

    mSolverR.solve();
    mSolverG.solve();
    mSolverB.solve();
    mSolverS.solve();
}



VoxelWorld::VoxelWorld(int width, int height, int worldWidth, int worldHeight, int worldLength)
: View(width, height), mRenderer{}, mChunks(worldWidth, worldHeight, worldLength)
, mSolverR(&mChunks, 0), mSolverG(&mChunks, 1)
, mSolverB(&mChunks, 2), mSolverS(&mChunks, 3)
, mMeshes(mRenderer.render(mChunks)) {

    mTextureShader.load(
            "../res/shader/texture_2d_in_3d/texture_2d_in_3d.glslv",
            "../res/shader/texture_2d_in_3d/texture_2d_in_3d.glslf");
    mTexture.load("../res/image/blocks.png");

    mCrosshairShader.load(
            "../res/shader/crosshair/crosshair.glslv",
            "../res/shader/crosshair/crosshair.glslf");
    mCrosshairMesh = Mesh(crosshair_vertices, 4, crosshair_attrs);

    mLineShader.load(
            "../res/shader/line/line.glslv",
            "../res/shader/line/line.glslf");

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initializeLight();
}



void VoxelWorld::onViewSizeChanged(int width, int height) {
    View::onViewSizeChanged(width, height);
    mCamera.setAspect(((float) width) / ((float) height));
}



void VoxelWorld::applyEvents(const Events& events, float elapsedTime) {
    View::applyEvents(events, elapsedTime);

    double curSpeed = mCamera.getSpeed();

    if (events.keyPressed(GLFW_KEY_LEFT_SHIFT)) {
        curSpeed *= 3;
    }

//    if (events.keyJustPressed(GLFW_KEY_F1)) {
//        mRenderer.setAmbientOcclusion(!mRenderer.getAmbientOcclusion());
//        for (int chY = 0; chY < mChunks.getHeight(); ++chY) {
//            for (int chZ = 0; chZ < mChunks.getLength(); ++chZ) {
//                for (int chX = 0; chX < mChunks.getWidth(); ++chX) {
//                    mChunks.getChunk(chX, chY, chZ).setModified(true);
//                }
//            }
//        }
//    }

    if (events.keyPressed(GLFW_KEY_W)) {
        mCamera.moveRelative(glm::vec3(-elapsedTime * curSpeed, 0, 0));
    }
    if (events.keyPressed(GLFW_KEY_S)) {
        mCamera.moveRelative(glm::vec3(elapsedTime * curSpeed, 0, 0));
    }
    if (events.keyPressed(GLFW_KEY_A)) {
        mCamera.moveRelative(glm::vec3(0, -elapsedTime * curSpeed, 0));
    }
    if (events.keyPressed(GLFW_KEY_D)) {
        mCamera.moveRelative(glm::vec3(0, elapsedTime * curSpeed, 0));
    }
    if (events.keyPressed(GLFW_KEY_SPACE)) {
        mCamera.moveDirect(glm::vec3(0, -elapsedTime * curSpeed, 0));
    }
    if (events.keyPressed(GLFW_KEY_LEFT_CONTROL)) {
        mCamera.moveDirect(glm::vec3(0, elapsedTime * curSpeed, 0));
    }

    if (events.isCursorDisabled()) {
        mCamera.addRotX(mCamera.getSensX() * -events.getDeltaX() / getWidth());
        mCamera.addRotY(mCamera.getSensY() * -events.getDeltaY() / getHeight());
        if (mCamera.getRotY() < -glm::radians(89.0f))
            mCamera.setRotY(-glm::radians(89.0f));
        else if (mCamera.getRotY() > glm::radians(89.0f))
            mCamera.setRotY(glm::radians(89.0f));
        mCamera.setRotation(glm::mat4(1));
        mCamera.rotate(glm::vec3(mCamera.getRotY(), mCamera.getRotX(), 0));
    }

    mHighlighting.clearBuffer();
    {
        glm::vec3 end, norm, iend;
        Voxel* voxel = mChunks.rayCast(mCamera.getPosition(), mCamera.getFront(), 10, end, norm, iend);
        if (voxel != nullptr) {

            mHighlighting.box(iend - glm::vec3(0.000001, 0.000001, 0.000001), glm::vec3(1.000002, 1.000002, 1.000002));

            if (events.buttonJustPressed(GLFW_MOUSE_BUTTON_1)) {

                int x = iend.x;
                int y = iend.y;
                int z = iend.z;

                mChunks.setVoxelGlobal(x, y, z, 0);

                mSolverR.remove(x, y, z);
                mSolverG.remove(x, y, z);
                mSolverB.remove(x, y, z);

                mSolverR.solve();
                mSolverG.solve();
                mSolverB.solve();

                if (mChunks.getLight(x, y+1, z, 3) == 0xF) {
                    for (int i = y; i >= 0; --i) {
                        if (mChunks.getVoxelGlobal(x, i, z).getId() != 0)
                            break;
                        mSolverS.add(x, i, z, 0xF);
                    }
                }

                mSolverR.add(x,y+1,z); mSolverG.add(x,y+1,z); mSolverB.add(x,y+1,z); mSolverS.add(x,y+1,z);
                mSolverR.add(x,y-1,z); mSolverG.add(x,y-1,z); mSolverB.add(x,y-1,z); mSolverS.add(x,y-1,z);
                mSolverR.add(x+1,y,z); mSolverG.add(x+1,y,z); mSolverB.add(x+1,y,z); mSolverS.add(x+1,y,z);
                mSolverR.add(x-1,y,z); mSolverG.add(x-1,y,z); mSolverB.add(x-1,y,z); mSolverS.add(x-1,y,z);
                mSolverR.add(x,y,z+1); mSolverG.add(x,y,z+1); mSolverB.add(x,y,z+1); mSolverS.add(x,y,z+1);
                mSolverR.add(x,y,z-1); mSolverG.add(x,y,z-1); mSolverB.add(x,y,z-1); mSolverS.add(x,y,z-1);

                mSolverR.solve();
                mSolverG.solve();
                mSolverB.solve();
                mSolverS.solve();

            } else if (events.buttonJustPressed(GLFW_MOUSE_BUTTON_2)) {

                static const int chosenBlock = 3;

                int x = (int)iend.x + (int)norm.x;
                int y = (int)iend.y + (int)norm.y;
                int z = (int)iend.z + (int)norm.z;

                if (!mChunks.voxelNotNull(0, 0, 0, x, y, z) && mChunks.voxelExists(0, 0, 0, x, y, z)) {
                    mChunks.setVoxelGlobal(x, y, z, 3);
//                    mChunks.setVoxelGlobal(z, y, z, mChunks.getVoxelGlobal((int)iend.x, (int)iend.y, (int)iend.z));

                    mSolverR.remove(x, y, z);
                    mSolverG.remove(x, y, z);
                    mSolverB.remove(x, y, z);
                    mSolverS.remove(x, y, z);

                    for (int i = y-1; i > 0 && mChunks.getVoxelGlobal(x, i, z).getId() == 0; --i)
                        mSolverS.remove(x, i, z);

                    mSolverR.solve();
                    mSolverG.solve();
                    mSolverB.solve();
                    mSolverS.solve();

                    if (chosenBlock == 3) {
                        mSolverR.add(x, y, z, 15);
                        mSolverG.add(x, y, z, 15);
                        mSolverB.add(x, y, z, 0);
                        mSolverR.solve();
                        mSolverG.solve();
                        mSolverB.solve();
                    }
                }
            }
        }
    }
    mHighlighting.render();
}



void VoxelWorld::update() {
    mRenderer.render(mChunks, mMeshes);
}



void VoxelWorld::draw() const {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projView = mCamera.getProjView();

    mTextureShader.use();
    mTextureShader.setProjView(mCamera.getProjView());
    mTexture.bind();

    for (int i = 0; i < mMeshes.size(); ++i) {
        mTextureShader.setModel(mMeshes.getModel(i));
        mMeshes.getMesh(i).draw();
    }

    glLineWidth(1);
    mCrosshairShader.use();
    mCrosshairMesh.draw(GL_LINES);

    glLineWidth(2);
    mLineShader.use();
    mLineShader.setProjView(projView);
    mHighlighting.draw();
}



void VoxelWorld::save(const std::string& filename) const {
    std::vector<uint> voxels (mChunks.getVolume() * Chunk::VOLUME);
    std::ofstream out (filename, std::ios::binary);
    for (int i = 0; i < mChunks.getVolume(); ++i) {
        const Chunk& chunk = mChunks.getChunk(i);
        for (int j = 0; j < Chunk::VOLUME; ++j) {
            const Voxel& voxel = chunk.getVoxel(j);
            voxels[i*Chunk::VOLUME+j] = voxel.getId();
        }
    }
    out.write(reinterpret_cast<const char*>(voxels.data()), voxels.size() * sizeof(uint));
}

void VoxelWorld::load(const std::string& filename) {
    std::vector<uint> voxels (mChunks.getVolume() * Chunk::VOLUME);
    std::ifstream in (filename, std::ios::binary);
    in.read(reinterpret_cast<char*>(voxels.data()), voxels.size() * sizeof(uint));
    for (int i = 0; i < mChunks.getVolume(); ++i) {
        Chunk& chunk = mChunks.getChunk(i);
        for (int j = 0; j < Chunk::VOLUME; ++j) {
            Voxel& voxel = chunk.getVoxel(j);
            int oldId = voxel.getId();
            voxel.setId(voxels[i*Chunk::VOLUME+j]);
            if (oldId != voxel.getId())
                chunk.setModified(true);
        }
    }
    update();
}