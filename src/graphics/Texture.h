#ifndef MINECRAFT_TEXTURE_H
#define MINECRAFT_TEXTURE_H

#include "../headers/includes.h"

class Texture {

    uint mId;
    uint mWidth, mHeight;

public:

    class TextureCreationException : public std::exception {};

    Texture(uint id = (uint)-1, uint width = (uint)-1, uint height = (uint)-1);

    ~Texture();

    void load(const std::string& filename);

    void bind() const;
};

#endif //MINECRAFT_TEXTURE_H