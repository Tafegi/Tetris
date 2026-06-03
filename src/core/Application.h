#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class GameController;

class Application
{
public:
    Application();
    ~Application();

    Application(const Application&)            = delete;
    Application& operator=(const Application&) = delete;

    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow                m_window;
    std::unique_ptr<GameController> m_controller;

    static constexpr unsigned int k_windowWidth  = 800;
    static constexpr unsigned int k_windowHeight = 700;
    static constexpr unsigned int k_fps          = 60;
};