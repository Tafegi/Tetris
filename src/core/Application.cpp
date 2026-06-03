// src/core/Application.cpp
#include "Application.h"
#include "controller/GameController.h"

// Destructor here — GameController is fully defined in this translation unit
Application::~Application() = default;

Application::Application()
    : m_window(sf::VideoMode({k_windowWidth, k_windowHeight}), "Tetris")
{
    m_window.setFramerateLimit(k_fps);
    m_controller = std::make_unique<GameController>(m_window);
}

void Application::run()
{
    sf::Clock clock;
    while (m_window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Application::processEvents()
{
    // SFML 3: pollEvent() returns std::optional<sf::Event>
    while (const std::optional<sf::Event> event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            m_window.close();

        m_controller->handleEvent(*event);
    }
}

void Application::update(float deltaTime)
{
    m_controller->update(deltaTime);
}

void Application::render()
{
    m_window.clear(sf::Color(15, 15, 25));
    m_controller->render();
    m_window.display();
}