#include "Window.h"

Window::Window()
	: Window("No name", { 640, 480 }, sf::Color::White)
{
}

Window::Window(const std::string& title, const sf::Vector2u& size, const sf::Color& clearColor)
	: windowTitle(title)
	, windowSize(size)
	, done(false)
	, fullscreen(false)
	, focused(true)
	, clearColor(clearColor)
	, currentRender(Render::twoDimensional)
	, imGuiUpdateClock()
{
	eventManager.addCallback(StateType(0), "Window_close", &Window::close, this);
}

Window::~Window()
{
	ImGui::SFML::Shutdown();
	window.close();
}

void Window::beginDraw()
{
	window.clear(clearColor);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::endDraw()
{
	ImGui::SFML::Render();
	window.display();
}

void Window::update()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::LostFocus)
		{
			focused = false;
			eventManager.setFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			focused = true;
			eventManager.setFocus(true);
		}
		eventManager.handleEvent(event);
	}
	ImGui::SFML::Update(window, imGuiUpdateClock.restart());
	eventManager.update();
}

void Window::setWindowSize(const sf::Vector2u& size)
{
	windowSize = size;
}

void Window::close(EventDetails* details)
{
	done = true;
}

void Window::draw(const sf::Drawable& drawable)
{
	window.draw(drawable);
}

void Window::renderImGui()
{
	start2D();
	ImGui::SFML::Render(window);
}

void Window::start2D()
{
	if (currentRender != Render::twoDimensional)
	{
		window.setActive(false);
		window.pushGLStates();
		currentRender = Render::twoDimensional;
	}
}

void Window::start3D()
{
	if (currentRender != Render::threeDimensional)
	{
		window.popGLStates();
		window.setActive(true);
		currentRender = Render::threeDimensional;
	}
}

void Window::startWindow()
{
	create();
}

bool Window::isDone() const
{
	return done;
}

bool Window::isFocused() const
{
	return focused;
}

bool Window::isFullscreen() const
{
	return fullscreen;
}

sf::Vector2u Window::getWindowSize() const
{
	return windowSize;
}

sf::Vector2i Window::getMousePosition() const
{
	return sf::Mouse::getPosition(window);
}

sf::RenderWindow* Window::getRenderWindow()
{
	return &window;
}

EventManager* Window::getEventManager()
{
	return &eventManager;
}

sf::Color Window::getClearColor() const
{
	return clearColor;
}

void Window::setClearColor(const sf::Color& color)
{
	clearColor = color;
}

void Window::destroy()
{
	window.setActive(false);
	ImGui::SFML::Shutdown(window);
	window.close();
}

void Window::create()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 3;

	auto style = (fullscreen ? sf::Style::Fullscreen | sf::Style::Close : sf::Style::Close | sf::Style::Titlebar);
	window.create({ windowSize.x, windowSize.y, 32 }, windowTitle, style, settings);
	window.setKeyRepeatEnabled(false);
	ImGui::SFML::Init(window);

	window.setActive(true);
	initGLEW();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glViewport(0, 0, windowSize.x, windowSize.y);
	window.setActive(false);
	window.pushGLStates();

	if (currentRender == Render::twoDimensional)
	{
		start2D();
	}
	else
	{
		start3D();
	}
}

void Window::initGLEW()
{
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::string excpetionMessage("Glew initialisation failed");
		printf("%s ERROR: %s\n", __func__, excpetionMessage.c_str());
		throw std::runtime_error(excpetionMessage);
	}
}
