#pragma once

#include <headers/includes.h>


class LightMap {

    std::vector<short> mMap;

public:

    LightMap();

    ubyte get(int x, int y, int z, int channel) const;
    ubyte getR(int x, int y, int z) const;
    ubyte getG(int x, int y, int z) const;
    ubyte getB(int x, int y, int z) const;
    ubyte getS(int x, int y, int z) const;

    void set(int x, int y, int z, int channel, int value);
    void setR(int x, int y, int z, int value);
    void setG(int x, int y, int z, int value);
    void setB(int x, int y, int z, int value);
    void setS(int x, int y, int z, int value);
};