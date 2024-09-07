#pragma once

/*
 * MinecraftClone
 * Copyright (C) © 2022  Petr Alexandrovich Sabanov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <headers/includes.h>

#include <engine/voxel/Voxel.h>
#include <engine/light/LightMap.h>

class Chunk {

	int mX, mY, mZ;
	std::vector<Voxel> mVoxels;
	LightMap mLightMap {};
	bool mModified = true;

public:

	inline static const int WIDTH = 32;
	inline static const int HEIGHT = 32;
	inline static const int LENGTH = 32;
	inline static const int VOLUME = WIDTH * HEIGHT * LENGTH;

	using VoxelGenerator = std::function<Voxel(uint,uint,uint)>;

	static bool voxelExists(int x, int y, int z);

	Chunk(int x = 0, int y = 0, int z = 0, const VoxelGenerator& generator = nullptr);

	void generateVoxels(const VoxelGenerator& generator);

	int getX() const;
	int getY() const;
	int getZ() const;
	void setX(int x);
	void setY(int y);
	void setZ(int z);

	Voxel& getVoxel(uint x, uint y, uint z);
	const Voxel& getVoxel(uint x, uint y, uint z) const;
	void setVoxel(uint x, uint y, uint z, const Voxel& voxel);

	ubyte getLight(int x, int y, int z, int channel) const;
	void setLight(int x, int y, int z, int channel, int value);

	bool isModified() const;
	void setModified(bool modified);

	Voxel& getVoxel(int index);
	const Voxel& getVoxel(int index) const;
	void setVoxel(int index, const Voxel& voxel);
};