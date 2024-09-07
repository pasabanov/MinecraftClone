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

#include <engine/view/View.h>
#include <engine/graphics/VoxelsRenderer.h>
#include <engine/graphics/Shader.h>
#include <engine/camera/Camera.h>
#include <engine/graphics/Texture2D.h>
#include <engine/graphics/LineBatch.h>
#include <engine/light/LightSolver.h>

class VoxelWorld : public View {

	inline static const float crosshair_vertices[] = {
			-0.01, -0.01,
			0.01, 0.01,

			-0.01, 0.01,
			0.01, -0.01
	};
	inline static const int crosshair_attrs[] = { 2, 0 };

	VoxelsRenderer mRenderer;
	ChunkHeap mChunks;
	MeshHeap mMeshes;

	LightSolver mSolverR;
	LightSolver mSolverG;
	LightSolver mSolverB;
	LightSolver mSolverS;

	Shader mTextureShader;
	Texture2D mTexture;

	Shader mCrosshairShader;
	Mesh mCrosshairMesh;

	Shader mLineShader;
	LineBatch mHighlighting;

	Camera mCamera;

	void initializeLight();

public:

	VoxelWorld(int width, int height, int worldWidth, int worldHeight, int worldLength);

	void onViewSizeChanged(int width, int height) override;

	void applyEvents(const Events &events, float elapsedTime) override;

	void update() override;

	void draw() const override;

	void save(const std::string& filename) const;
	void load(const std::string& filename);
};