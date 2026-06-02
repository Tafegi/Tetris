#pragma once

#include <SFML/Window/Event.hpp>
#include "model/game/Game.h"
#include "StateMachine.h"

namespace controller
{
    class InputController
    {
    public:
        InputController();

        void process(const sf::Event& event,
                     StateMachine& stateMachine,
                     model::Game& game);

        void update(float dt, model::Game& game);

    private:
        void handleMenuInput(const sf::Event& event, StateMachine& sm);
        void handleGameInput(const sf::Event& event, model::Game& game);
        void handlePauseInput(const sf::Event& event, StateMachine& sm);

    private:
        // DAS (Delayed Auto Shift) для плавного зсування фігур
        float dasTimer_{0.f};
        float dasDelay_{0.15f};

        // ARR (Auto Repeat Rate)
        float arrTimer_{0.f};
        float arrRate_{0.03f};

        bool leftHeld_{false};
        bool rightHeld_{false};
        bool softDropHeld_{false};
    };
}