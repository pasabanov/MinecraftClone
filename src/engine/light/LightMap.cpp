#include "LightMap.h"

#include "../voxel/Chunk.h"


LightMap::LightMap() : mMap(Chunk::VOLUME) {}



ubyte LightMap::get(int x, int y, int z, int channel) const {
    return (mMap[(y*Chunk::LENGTH + z)*Chunk::WIDTH + x] >> channel * 4) & 0xF;
}

ubyte LightMap::getR(int x, int y, int z) const {
    return mMap[(y*Chunk::LENGTH + z)*Chunk::WIDTH + x] & 0xF;
}

ubyte LightMap::getG(int x, int y, int z) const {
    return (mMap[(y*Chunk::LENGTH + z)*Chunk::WIDTH + x] >> 4) & 0xF;
}

ubyte LightMap::getB(int x, int y, int z) const {
    return (mMap[(y*Chunk::LENGTH + z)*Chunk::WIDTH + x] >> 8) & 0xF;
}

ubyte LightMap::getS(int x, int y, int z) const {
    return (mMap[(y*Chunk::LENGTH + z)*Chunk::WIDTH + x] >> 12) & 0xF;
}



void LightMap::set(int x, int y, int z, int channel, int value) {
    int index = (y*Chunk::LENGTH + z)*Chunk::WIDTH + x;
    mMap[index] = mMap[index] & (~(0xF << channel * 4)) | (value << channel * 4);
}

void LightMap::setR(int x, int y, int z, int value) {
    int index = (y*Chunk::LENGTH + z)*Chunk::WIDTH + x;
    mMap[index] = mMap[index] & 0xFFF0 | value;
}

void LightMap::setG(int x, int y, int z, int value) {
    int index = (y*Chunk::LENGTH + z)*Chunk::WIDTH + x;
    mMap[index] = mMap[index] & 0xFF0F | (value << 4);
}

void LightMap::setB(int x, int y, int z, int value) {
    int index = (y*Chunk::LENGTH + z)*Chunk::WIDTH + x;
    mMap[index] = mMap[index] & 0xF0FF | (value << 8);
}

void LightMap::setS(int x, int y, int z, int value) {
    int index = (y*Chunk::LENGTH + z)*Chunk::WIDTH + x;
    mMap[index] = mMap[index] & 0x0FFF | (value << 12);
}