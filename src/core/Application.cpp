#include "Application.h"
#include "Logger.h"
#include "controller/GameController.h"

#include <chrono>

namespace core
{
    Application::Application()
        : logger_(std::make_unique<Logger>("logs.txt"))
        , window_(sf::VideoMode({1280u, 720u}), "Tetris")
        , controller_(std::make_unique<controller::GameController>(window_))
    {
        window_.setFramerateLimit(60);
        logger_->info("Application started");
    }

    Application::~Application()
    {
        logger_->info("Application shutdown");
    }

    void Application::run()
    {
        using clock = std::chrono::high_resolution_clock;
        auto lastTime = clock::now();

        while (running_ && window_.isOpen())
        {
            auto now = clock::now();
            std::chrono::duration<float> delta = now - lastTime;
            lastTime = now;

            processEvents();

            if (controller_->stateMachine().shouldExit())
            {
                running_ = false;
                window_.close();
                break;
            }

            update(delta.count());
            render();
        }
    }

    void Application::processEvents()
    {
        while (const std::optional event = window_.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                running_ = false;
                window_.close();
                return;
            }

            controller_->handleEvent(*event);
        }
    }

    void Application::update(float dt)
    {
        if (controller_)
            controller_->update(dt);
    }

    void Application::render()
    {
        if (controller_)
            controller_->render();
    }
}