#pragma once

#include "GUI/SpaceSimulationImGui.h"
#include "AppFramework/Serializer/Serializer.h"
#include "AppFramework/StateManager/StateManager.h"
#include "3DRenderer/Camera/CameraManagerToSFMLFrameworkAdapter.h"
#include "3DObjects/CoordinateSystemAxes.h"
#include "ObjectCreators/PlanetCreator.h"

#include <ranges>

class SpaceSimulationImGui;

class StateSpaceSimulation : public BaseState, public EditableViaImGui
{
public:
	friend class SpaceSimulationImGui;

	StateSpaceSimulation(StateManager* stateManager, Render render = Render::threeDimensional);

	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void activate() override;
	virtual void deactivate() override;
	virtual void update(const sf::Time& time) override;
	virtual void draw() override;

private:
	enum class Mouse
	{
		LEFT,
		RIGHT
	};

	void enableEvents();
	void disableEvents();
	void resetSimulation();
	void renderObject(const Renderable& renderable);
	void addPlanetToSimulation(std::shared_ptr<RenderablePlanet> planet);
	void removePlanetFromSimulation(std::shared_ptr<RenderablePlanet> planet);
	void addObjectToRender(std::shared_ptr<Renderable> object);
	void removeObjectToRender(std::shared_ptr<Renderable> object);
	void focusPlanet(std::shared_ptr<RenderablePlanet> planet);
	void focusCenter(EventDetails* details);
	void switchSimulationState(EventDetails* e);
	void mouseLeftClick(EventDetails* details);
	void mouseRightClick(EventDetails* details);
	void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool begiImGui) override;
	void saveSimulation(const std::filesystem::path& filePath);
	void loadSimulation(const std::filesystem::path& filePath);

	bool pauseSimulation;
	bool renderCoordinateAxes;
	PhysicalUnit simulationSpeed;
	PhysicalUnit gravitationalConstant;
	SceneContext sceneContext;
	Serializer serializer;
	std::shared_ptr<CoordinateSystemAxes> coordinateSystemAxes;
	std::shared_ptr<RenderablePlanet> focusedPlanet;
	std::list<std::shared_ptr<Renderable>> objectsToRender;
	std::list<std::shared_ptr<RenderablePlanet>> planets;
	std::unique_ptr<SpaceSimulationImGui> simulationGui;
	std::shared_ptr<TextureManager> textureManager;
	std::unique_ptr<PlanetCreator> planetCreator;

	void addCallbacks();
	void removeCallbacks();
	void handleMouse(EventDetails* details, Mouse mouseButton);
};

