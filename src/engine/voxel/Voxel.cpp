#include <engine/voxel/Voxel.h>

Voxel::Voxel(uint id) : mId(id) {}

uint& Voxel::getId() {
	return mId;
}

uint Voxel::getId() const {
	return mId;
}

void Voxel::setId(uint id) {
	mId = id;
}

bool Voxel::operator==(const Voxel& other) const {
	return mId == other.mId;
}