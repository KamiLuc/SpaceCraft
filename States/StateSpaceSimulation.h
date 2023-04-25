#pragma once

#include "../AppFramework/StateManager/StateManager.h"
#include "../AppFramework/StateManager/BaseState.h"
#include "../3DRenderer/Camera/CameraManagerToSFMLFrameworkAdapter.h"
#include "../3DRenderer/Light.h"
#include "../3DObjects/Sphere.h"
#include "../3DRenderer/Texture.h"
#include "../3DRenderer/Material.h"

class StateSpaceSimulation : public BaseState
{
public:
	using BaseState::BaseState;

	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void activate() override;
	virtual void deactivate() override;
	virtual void update(const sf::Time& time) override;
	virtual void draw() override;

private:
	std::unique_ptr<CameraManagerToSFMLFrameworkAdapter> cameraManager;
	std::unique_ptr<Light> mainLight;
	std::unique_ptr<Material> shinyMaterial;
	std::unique_ptr<Material> dullMaterial;
	std::unique_ptr<Sphere> earth;
	std::unique_ptr<Sphere> sun;
	std::unique_ptr<Texture> earthTexture;
	std::unique_ptr<Texture> sunTexture;
	std::unique_ptr<Texture> brickTexture;

	const UniformLocations* currentUniformLocations;

	std::vector<Shader*> shaders{};
	std::vector<BasicMesh*> meshes{};

	void changeShader(const std::string& shader);
};

