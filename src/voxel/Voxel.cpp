#include "Voxel.h"



Voxel::Voxel(uint id) : mId(id) {}



uint Voxel::getId() const {
    return mId;
}



void Voxel::setId(uint id) {
    mId = id;
}