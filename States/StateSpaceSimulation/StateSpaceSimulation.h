#pragma once

#include "SpaceSimulationSettings.h"
#include "GUI/SpaceSimulationGUI.h"
#include "AppFramework/Serializer/Serializer.h"
#include "AppFramework/StateManager/StateManager.h"
#include "3DRenderer/Camera/CameraManagerToSFMLFrameworkAdapter.h"
#include "3DRenderer/Skybox.h"
#include "3DObjects/CoordinateSystemAxes.h"
#include "ObjectCreators/PlanetCreator.h"

#include <ranges>

class StateSpaceSimulation : public BaseState
{
public:
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

	void renderObject(const Renderable& renderable);
	void focusPlanet(std::shared_ptr<RenderablePlanet> planet);
	void focusCenter(EventDetails* details);
	void switchSimulationState(EventDetails* e);
	void mouseLeftClick(EventDetails* details);
	void mouseRightClick(EventDetails* details);

	SpaceSimulationSettings simulationSettings;
	PhysicalUnit gravitationalConstant;
	SceneContext sceneContext;
	Serializer serializer;

	//make unique
	std::unique_ptr<CoordinateSystemAxes> coordinateSystemAxes;
	std::unique_ptr<SpaceSimulationGUI> simulationGui;
	std::unique_ptr<Skybox> skybox;
	std::unique_ptr<PlanetCreator> planetCreator;

	void addCallbacks();
	void removeCallbacks();
	void handleMouse(EventDetails* details, Mouse mouseButton);
};

