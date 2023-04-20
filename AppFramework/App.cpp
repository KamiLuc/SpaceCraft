#include "App.h"

App::App() : window("SpaceCraft", { 1366,768 }, sf::Color::White), sharedContext(),
stateManager(&this->sharedContext), shaderManager("Shaders")
{
	this->sharedContext.window = &this->window;
	this->sharedContext.eventManager = this->window.getEventManager();
	this->sharedContext.shaderManager = &this->shaderManager;

	this->window.start3D();
	this->shaderManager.loadAndCompileShaders();

	this->stateManager.switchTo(StateType::Intro);
}

App::~App()
{
}

void App::handleInput()
{
}

void App::update()
{
	this->window.update();
	this->stateManager.update(this->elapsedTime);
}

void App::lateUpdate()
{
	this->stateManager.processRequest();
	this->restartClock();
}

void App::render()
{
	this->window.beginDraw();
	this->stateManager.draw();
	this->window.endDraw();
}

sf::Time App::getElapsedTime() const
{
	return this->elapsedTime;
}

void App::restartClock()
{
	this->elapsedTime = this->clock.restart();
}

Window* App::getWindow()
{
	return &this->window;
}
