#ifndef MINECRAFT_TEXTURE2D_H
#define MINECRAFT_TEXTURE2D_H

#include "../headers/includes.h"

class Texture2D {

    uint mId = GL_NONE;
    uint mWidth = 0, mHeight = 0;

    void glDelete();

public:

    class TextureCreationException : public std::exception {};

    Texture2D(uint id = GL_NONE, uint width = GL_NONE, uint height = GL_NONE);
    Texture2D(Texture2D&& other);

    ~Texture2D();

    Texture2D& operator=(Texture2D&& other);

    void load(const std::string& filename);

    void bind() const;
};

#endif //MINECRAFT_TEXTURE2D_H