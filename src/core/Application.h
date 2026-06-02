#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Logger.h"

namespace controller
{
    class GameController;
}

namespace core
{
    class Application
    {
    public:
        Application();
        ~Application();

        void run();

    private:
        void processEvents();
        void update(float dt);
        void render();

    private:
        bool running_{true};
        std::unique_ptr<Logger> logger_;
        sf::RenderWindow window_;
        std::unique_ptr<controller::GameController> controller_;
    };
}