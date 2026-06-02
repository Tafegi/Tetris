#pragma once

#include <SFML/Graphics.hpp>

#include "../interfaces/IState.h"
#include "../controller/StateMachine.h"
#include "../controller/InputController.h"
#include "../model/game/Game.h"
#include "../view/GameView.h" // Додаємо підключення GameView

namespace state
{
    class PlayingState final : public IState
    {
    public:
        PlayingState(sf::RenderWindow& window,
                     controller::StateMachine& stateMachine,
                     model::Game& game,
                     controller::InputController& input);

        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render() override;

    private:
        void drawUI();

    private:
        sf::RenderWindow& window_;
        controller::StateMachine& stateMachine_;

        model::Game& game_;
        controller::InputController& input_;

        view::GameView gameView_; // Об'єкт для відображення ігрового поля

        sf::Font font_;
        sf::Text hudText_;
    };
}