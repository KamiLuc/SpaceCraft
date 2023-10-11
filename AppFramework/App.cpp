#include "App.h"

App::App()
	: window("SpaceCraft", { 1620, 900 }, sf::Color::White), sharedContext()
	, stateManager(&sharedContext)
{
	shaderManager = std::make_shared<ShaderManager>();
	textureManager = std::make_shared<TextureManager>();

	sharedContext.window = &window;
	sharedContext.eventManager = window.getEventManager();
	sharedContext.shaderManager = shaderManager;
	sharedContext.textureManager = textureManager;

	auto& settings = Settings::GlobalSettings::getInstance();

	shaderManager->setPath(settings.getShadersPath());
	textureManager->setPath(settings.getTexturesPath());

	window.start3D();
	shaderManager->loadAndCompileShaders();

	stateManager.switchTo(StateType::Intro);
}

App::~App()
{
}

void App::handleInput()
{
}

void App::update()
{
	window.update();
	stateManager.update(elapsedTime);
}

void App::lateUpdate()
{
	stateManager.processRequest();
	restartClock();
}

void App::render()
{
	window.beginDraw();
	stateManager.draw();
	window.endDraw();
}

sf::Time App::getElapsedTime() const
{
	return elapsedTime;
}

void App::restartClock()
{
	elapsedTime = clock.restart();
}

Window* App::getWindow()
{
	return &window;
}
