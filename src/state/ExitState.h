#pragma once

#include <SFML/Graphics.hpp>

#include "../interfaces/IState.h"
#include "../controller/StateMachine.h"

namespace state
{
    class ExitState final : public IState
    {
    public:
        ExitState(sf::RenderWindow& window,
                  controller::StateMachine& stateMachine);

        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render() override;

    private:
        sf::RenderWindow& window_;
        controller::StateMachine& stateMachine_;
    };
}