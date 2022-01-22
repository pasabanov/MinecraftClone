#ifndef MINECRAFT_VOXEL_H
#define MINECRAFT_VOXEL_H

#include "../headers/includes.h"

class Voxel {

    uint mId;

public:

    Voxel(uint id = 0);

    uint getId() const;

    void setId(uint id);
};

#endif //MINECRAFT_VOXEL_H