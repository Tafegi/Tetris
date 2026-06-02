#pragma once

#include <SFML/Graphics.hpp>

#include "../interfaces/IState.h"
#include "../controller/StateMachine.h"

namespace state
{
    class PauseState final : public IState
    {
    public:
        PauseState(sf::RenderWindow& window,
                   controller::StateMachine& stateMachine);

        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render() override;

    private:
        void drawUI();

    private:
        sf::RenderWindow& window_;
        controller::StateMachine& stateMachine_;

        sf::Font font_;
        sf::Text titleText_;
        sf::Text hintText_;
    };
}