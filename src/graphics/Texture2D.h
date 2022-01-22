#ifndef MINECRAFT_TEXTURE2D_H
#define MINECRAFT_TEXTURE2D_H

#include "../headers/includes.h"

class Texture2D {

    uint mId;
    uint mWidth, mHeight;

public:

    class TextureCreationException : public std::exception {};

    Texture2D(uint id = (uint)-1, uint width = (uint)-1, uint height = (uint)-1);
    Texture2D(Texture2D&& other);

    ~Texture2D();

    Texture2D& operator=(Texture2D&& other);

    void load(const std::string& filename);

    void bind() const;
};

#endif //MINECRAFT_TEXTURE2D_H