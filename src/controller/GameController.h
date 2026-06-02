#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "model/game/Game.h"
#include "view/GameView.h"
#include "view/GameOverView.h"
#include "view/MenuView.h"
#include "view/PauseView.h"
#include "view/StatisticsView.h"
#include "view/SettingsView.h"

#include "InputController.h"
#include "StateMachine.h"

namespace controller
{
    class GameController
    {
    public:
        explicit GameController(sf::RenderWindow& window);

        void handleEvent(const sf::Event& event);
        void update(float dt);
        void render();

        StateMachine& stateMachine() { return stateMachine_; }

    private:
        void updateGame(float dt);
        void updateMenu(float dt);
        void updatePause(float dt);
        void updateGameOver(float dt);

    private:
        sf::RenderWindow& window_;

        model::Game game_;

        view::GameView     gameView_;
        view::MenuView     menuView_;
        view::PauseView    pauseView_;
        view::GameOverView gameOverView_;
        view::StatisticsView statisticsView_;
        view::SettingsView   settingsView_;

        InputController input_;
        StateMachine    stateMachine_;
    };
}