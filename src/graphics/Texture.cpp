#include "Texture.h"



Texture::Texture(uint id, uint width, uint height) : mId(id), mWidth(width), mHeight(height) {}



Texture::~Texture() {
    glDeleteTextures(1, &mId);
}



void Texture::load(const std::string& filename) {

    uchar* image = SOIL_load_image(
            filename.c_str(),
            (int*)&mWidth,
            (int*)&mHeight,
            nullptr,
            SOIL_LOAD_RGBA);

    for (uint j = 0; j < mHeight/2; ++j) {
        for (uint i = 0; i < mWidth; ++i) {
            uint& pixel1 = ((uint*)(image))[j*mWidth+i];
            uint& pixel2 = ((uint*)(image))[(mHeight-1-j)*mWidth+i];
            uint tmp = pixel1;
            pixel1 = pixel2;
            pixel2 = tmp;
        }
    }

    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            mWidth,
            mHeight,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            image);
    glBindTexture(GL_TEXTURE_2D, -1);

    SOIL_free_image_data(image);
}


void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, mId);
}