#pragma once

#include "Interfaces/Renderable.h"
#include "3DRenderer/Mesh/BasicMesh.h"
#include "3DRenderer/Texture/CubeMapTexture.h"

class Skybox : public Renderable
{
public:
	Skybox(std::shared_ptr<CubeMapTexture> skyboxTexture);

	void render(SceneContext& sceneContext) const override;

private:
	std::shared_ptr<CubeMapTexture> cubeMapTexture;
	BasicMesh mesh;
};
