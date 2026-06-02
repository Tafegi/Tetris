#pragma once

#include <SFML/Graphics.hpp>

#include "../interfaces/IState.h"
#include "../controller/StateMachine.h"
#include "../model/game/Game.h"

namespace state
{
    class GameOverState final : public IState
    {
    public:
        GameOverState(sf::RenderWindow& window,
                      controller::StateMachine& stateMachine,
                      const model::Game& game);

        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render() override;

    private:
        void drawUI();

    private:
        sf::RenderWindow& window_;
        controller::StateMachine& stateMachine_;
        const model::Game& game_;

        sf::Font font_;
        sf::Text titleText_;
        sf::Text statsText_;
    };
}