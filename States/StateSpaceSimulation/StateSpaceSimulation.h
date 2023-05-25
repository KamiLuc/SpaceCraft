#pragma once

#include "../../AppFramework/StateManager/StateManager.h"
#include "../../AppFramework/StateManager/BaseState.h"
#include "../../3DRenderer/Camera/CameraManagerToSFMLFrameworkAdapter.h"
#include "../../3DRenderer/Light.h"
#include "../../3DObjects/TexturedSphere.h"
#include "../../3DRenderer/Texture/Texture.h"
#include "../../3DRenderer/Material.h"
#include "../../3DRenderer/Mesh/TexturedMesh.h"
#include "../../3DRenderer/Mesh/ColoredMesh.h"
#include "../../3DObjects/CoordinateSystemAxes.h"
#include "../../3DObjects/Interfaces/Planet.h"
#include "SpaceSimulationImGui.h"


class SpaceSimulationImGui;

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
	void renderObject(const Renderable& renderable);

	std::shared_ptr<Planet> createTexturedPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
		float scale, const std::string& identifier, const Texture& texture);

	std::shared_ptr<Planet> createColoredPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
		float scale, const std::string& identifier, const glm::vec4& color);

	void addPlanetToSimulation(std::shared_ptr<Planet> planet);
	void removePlanetFromSimulation(std::shared_ptr<Planet> planet);

private:
	std::unique_ptr<CameraManagerToSFMLFrameworkAdapter> cameraManager;
	std::unique_ptr<Light> mainLight;
	std::unique_ptr<Material> shinyMaterial;
	std::unique_ptr<Material> dullMaterial;

	std::shared_ptr<CoordinateSystemAxes> coordinateSystemAxes;

	const Shader* lastUsedShader;

	std::vector<std::shared_ptr<Renderable>> objectsToRender;
	std::vector<std::shared_ptr<Planet>> planets;

	std::unique_ptr<SpaceSimulationImGui> simulationGui;

	TextureManager* texturesManager;
	ShaderManager* shaderManager;

	void addCallbacks();
	void removeCallbacks();
};

