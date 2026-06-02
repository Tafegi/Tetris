#pragma once

#include <SFML/Graphics.hpp>

#include "../interfaces/IState.h"
#include "../controller/StateMachine.h"
#include "../view/MenuView.h"

namespace state
{
    class MainMenuState final : public IState
    {
    public:
        MainMenuState(sf::RenderWindow& window,
                      controller::StateMachine& stateMachine);

        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render() override;

    private:
        sf::RenderWindow& window_;
        controller::StateMachine& stateMachine_;

        view::MenuView menuView_;
    };
}