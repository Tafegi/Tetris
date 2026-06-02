#pragma once

#include <memory>
#include "Logger.h"

// Forward declarations у правильних просторах імен
namespace controller
{
    class GameController;
    class StateMachine;
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

        // Використовуємо точні типи з потрібного namespace
        std::unique_ptr<controller::GameController> controller_;
        //std::unique_ptr<controller::StateMachine> stateMachine_;
    };
}