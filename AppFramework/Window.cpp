#include "Window.h"

Window::Window() : Window("No name", {640, 480}, sf::Color::White)
{
}

Window::Window(const std::string& title, const sf::Vector2u& size, const sf::Color& clearColor)
	: windowTitle(title), windowSize(size), done(false), fullscreen(false), focused(true), clearColor(clearColor)
{
	this->create();

	this->eventManager.addCallback(StateType(0), "Fullscreen_toggle",
		&Window::toggleFullscreen, this);
	this->eventManager.addCallback(StateType(0), "Window_close",
		&Window::close, this);

}

Window::~Window()
{
	this->window.close();
}

void Window::beginDraw()
{
	this->window.clear(this->clearColor);
}

void Window::endDraw()
{
	this->window.display();
}

void Window::update()
{
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus)
		{
			this->focused = false;
			this->eventManager.setFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			this->focused = true;
			this->eventManager.setFocus(true);
		}
		this->eventManager.handleEvent(event);
	}
	this->eventManager.update();
}

void Window::close(EventDetails* details)
{
	this->done = true;
}

void Window::toggleFullscreen(EventDetails* details)
{
	this->fullscreen = !this->fullscreen;
	this->destroy();
	this->create();
}

void Window::draw(const sf::Drawable& drawable)
{
	this->window.draw(drawable);
}

void Window::start2D()
{
	this->window.pushGLStates();
}

void Window::stop2D()
{
	this->window.popGLStates();
}

void Window::start3D()
{
	this->window.setActive(true);
}

void Window::stop3D()
{
	this->window.setActive(false);
}

bool Window::isDone() const
{
	return this->done;
}

bool Window::isFocused() const
{
	return this->focused;
}

bool Window::isFullscreen() const
{
	return this->fullscreen;
}

sf::Vector2u Window::getWindowSize() const
{
	return this->windowSize;
}

sf::RenderWindow* Window::getRenderWindow()
{
	return &this->window;
}

EventManager* Window::getEventManager()
{
	return &this->eventManager;
}

void Window::setClearColor(const sf::Color& color)
{
	this->clearColor = color;
}

void Window::destroy()
{
	this->window.close();
}

void Window::create()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 3;

	auto style = (this->fullscreen ? sf::Style::Fullscreen :  sf::Style::Close | sf::Style::Titlebar);
	window.create({ this->windowSize.x, this->windowSize.y, 32 }, this->windowTitle, style, settings);
	
	window.setActive(true);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, this->windowSize.y, this->windowSize.x);
	window.setActive(false);

	this->initGLEW();
}

void Window::initGLEW()
{
	this->window.setActive(true);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::string excpetionMessage("Glew initialisation failed");
		printf("%s ERROR: %s\n", __func__, excpetionMessage.c_str());
		throw std::runtime_error(excpetionMessage);
	}
	this->window.setActive(false);
}
