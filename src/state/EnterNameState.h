#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "../interfaces/IState.h"
#include "../controller/StateMachine.h"

namespace state
{
    class EnterNameState final : public IState
    {
    public:
        EnterNameState(sf::RenderWindow& window,
                       controller::StateMachine& stateMachine);

        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render() override;

    private:
        // В SFML 3 замість sf::Uint32 використовується стандартний char32_t
        void processInput(char32_t unicode);
        void drawUI();

    private:
        sf::RenderWindow& window_;
        controller::StateMachine& stateMachine_;

        std::string playerName_;

        sf::Font font_;
        sf::Text titleText_;
        sf::Text inputText_;
    };
}