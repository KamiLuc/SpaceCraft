#pragma once

#include "SpaceSimulationImGui.h"
#include "../../AppFramework/StateManager/StateManager.h"
#include "../../3DRenderer/Camera/CameraManagerToSFMLFrameworkAdapter.h"
#include "../../3DRenderer/Light/Light.h"
#include "../../3DRenderer/Material.h"
#include "../../3DObjects/CoordinateSystemAxes.h"
#include "../../3DObjects/ColoredPlanet.h"
#include "../../3DObjects/TexturedPlanet.h"

class SpaceSimulationImGui;

class StateSpaceSimulation : public BaseState, public EditableViaImGui
{
public:
	StateSpaceSimulation(StateManager* stateManager, Render render = Render::twoDimensional);

	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void activate() override;
	virtual void deactivate() override;
	virtual void update(const sf::Time& time) override;
	virtual void draw() override;
	void renderObject(const Renderable& renderable);

	std::shared_ptr<TexturedPlanet> createTexturedPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
		const Measure<1>& radius, float scale, const std::string& identifier, const Texture& texture);

	std::shared_ptr<ColoredPlanet> createColoredPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
		const Measure<1>& radius, float scale, const std::string& identifier, const glm::vec4& color);

	std::list<std::shared_ptr<RenderablePlanet>>& getPlanetsRef();

	Light& getMainLightRef();
	CameraManager& getCameraManagerRef();
	Measure<1>& getSimulationSpeedRef();

	void addPlanetToSimulation(std::shared_ptr<RenderablePlanet> planet);
	void removePlanetFromSimulation(std::shared_ptr<RenderablePlanet> planet);

	void addObjectToRender(std::shared_ptr<Renderable> object);
	void removeObjectToRender(std::shared_ptr<Renderable> object);

	void focusPlanet(std::shared_ptr<Planet> planet);

	void focusCenter(EventDetails* details);
	void switchSimulationState(EventDetails* e);
	void mouseLeftClick(EventDetails* details);
	void mouseRightClick(EventDetails* details);

	void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID) override;

private:

	bool pauseSimulation;
	bool renderCoordinateAxes;

	Measure<1> simulationSpeed;
	Measure<1> gravitationalConstant;

	std::unique_ptr<CameraManagerToSFMLFrameworkAdapter> cameraManager;
	std::unique_ptr<Light> mainLight;
	std::unique_ptr<Material> shinyMaterial;
	std::unique_ptr<Material> dullMaterial;

	std::shared_ptr<CoordinateSystemAxes> coordinateSystemAxes;
	std::shared_ptr<RenderablePlanet> focusedPlanet;

	std::list<std::shared_ptr<Renderable>> objectsToRender;
	std::list<std::shared_ptr<RenderablePlanet>> planets;

	std::unique_ptr<SpaceSimulationImGui> simulationGui;

	TextureManager* texturesManager;
	ShaderManager* shaderManager;

	void addCallbacks();
	void removeCallbacks();
};

