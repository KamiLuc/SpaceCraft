#include "App.h"

App::App() : window("SpaceCraft", {1024,768}), sharedContext(), stateManager(&this->sharedContext)
{
	this->sharedContext.window = &this->window;
	this->sharedContext.eventManager = this->window.getEventManager();

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
