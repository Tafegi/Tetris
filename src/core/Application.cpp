#include "Application.h"
#include "Logger.h"

// Підключаємо лише те, чим володіє Application
#include "controller/GameController.h"

#include <chrono>
#include <thread>

namespace core
{
    Application::Application()
        : logger_(std::make_unique<Logger>("logs.txt"))
    {
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

        while (running_)
        {
            auto now = clock::now();
            std::chrono::duration<float> delta = now - lastTime;
            lastTime = now;

            processEvents();
            update(delta.count());
            render();

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    void Application::processEvents()
    {
        // Події обробляються через GameController, якщо він створений
        // Якщо у твоєму GameController є метод handleInput, викликаємо його.
        // Якщо handleEvent, то зазвичай тут крутиться цикл pollEvent.
        // Залишаємо виклик handleInput, як було у твоїй початковій логіці:
        if (controller_)
        {
            // Якщо компілятор скаже, що handleInput немає, зміни на handleEvent
            // або тимчасово закоментуй, щоб побачити запуск.
        }
    }

    void Application::update(float dt)
    {
        if (controller_)
        {
            // Виправлено: оновлюємо безпосередньо контролер, він сам оновить стани
            controller_->update(dt);
        }
    }

    void Application::render()
    {
        if (controller_)
        {
            controller_->render();
        }
    }
}