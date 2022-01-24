#include "VoxelWorld.h"



VoxelWorld::VoxelWorld(int width, int height, int worldWidth, int worldHeight, int worldLength)
: View(width, height), mRenderer{}, mChunks(worldWidth, worldHeight, worldLength), mMeshes(mRenderer.render(mChunks)) {

    mTextureShader.load(
            "../res/shaders/texture_2d_in_3d/texture_2d_in_3d.glslv",
            "../res/shaders/texture_2d_in_3d/texture_2d_in_3d.glslf");
    mTexture.load("../res/images/blocks.png");

    mCrosshairShader.load(
            "../res/shaders/crosshair/crosshair.glslv",
            "../res/shaders/crosshair/crosshair.glslf");
    mCrosshairMesh = Mesh(crosshair_vertices, 4, crosshair_attrs);

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

    if (events.keyJustPressed(GLFW_KEY_F1)) {
        mRenderer.setAmbientOcclusion(!mRenderer.getAmbientOcclusion());
        for (int chY = 0; chY < mChunks.getHeight(); ++chY) {
            for (int chZ = 0; chZ < mChunks.getLength(); ++chZ) {
                for (int chX = 0; chX < mChunks.getWidth(); ++chX) {
                    mChunks.getChunk(chX, chY, chZ).setModified(true);
                }
            }
        }
    }

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

    if (events.buttonJustPressed(GLFW_MOUSE_BUTTON_1)
        || events.buttonJustPressed(GLFW_MOUSE_BUTTON_2)) {
        glm::vec3 end, norm, iend;
        Voxel* voxel = mChunks.rayCast(mCamera.getPosition(), mCamera.getFront(), 10, end, norm, iend);
        if (voxel != nullptr) {
            if (events.buttonJustPressed(GLFW_MOUSE_BUTTON_1)) {
                mChunks.setVoxelGlobal((int)iend.x, (int)iend.y, (int)iend.z, 0);
            } else if (events.buttonJustPressed(GLFW_MOUSE_BUTTON_2)) {
                int x = (int)iend.x + (int)norm.x;
                int y = (int)iend.y + (int)norm.y;
                int z = (int)iend.z + (int)norm.z;
                if (!mChunks.voxelNotNull(0, 0, 0, x, y, z))
//                        chunks.setVoxelGlobal((int)iend.x + (int)norm.x, iend.y + (int)norm.y, iend.z + (int)norm.z, 2);
                    mChunks.setVoxelGlobal((int)iend.x + (int)norm.x, iend.y + (int)norm.y, iend.z + (int)norm.z, mChunks.getVoxelGlobal((int)iend.x, (int)iend.y, (int)iend.z));
            }
        }
    }
}



void VoxelWorld::update() {
    mRenderer.render(mChunks, mMeshes);
}



void VoxelWorld::draw() const {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mTextureShader.use();
    mTextureShader.setProjView(mCamera.getProjView());
    mTexture.bind();

    for (int i = 0; i < mMeshes.size(); ++i) {
        mTextureShader.setModel(mMeshes.getModel(i));
        mMeshes.getMesh(i).draw();
    }
    mCrosshairShader.use();
    mCrosshairMesh.draw(GL_LINES);
}