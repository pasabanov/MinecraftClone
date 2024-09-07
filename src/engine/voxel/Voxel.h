#pragma once

#include <headers/includes.h>

class Voxel {

    uint mId;

public:

    Voxel(uint id = 0);

    uint& getId();
    uint getId() const;
    void setId(uint id);

    bool operator==(const Voxel& other) const;
};