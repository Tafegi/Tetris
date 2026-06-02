#include "PauseState.h"

namespace state
{
    PauseState::PauseState(sf::RenderWindow& window,
                           controller::StateMachine& stateMachine)
        : window_(window)
        , stateMachine_(stateMachine)
        , titleText_(font_) // Явна ініціалізація шрифту для SFML 3
        , hintText_(font_)  // Явна ініціалізація шрифту для SFML 3
    {
        if (!font_.openFromFile("assets/fonts/Roboto-Regular.ttf")) {
            // обробка помилки за бажанням
        }

        titleText_.setCharacterSize(48);
        titleText_.setString("PAUSED");
        titleText_.setFillColor(sf::Color::White);
        titleText_.setPosition({120.f, 80.f}); // Фігурні дужки для sf::Vector2f

        hintText_.setCharacterSize(22);
        hintText_.setString("Press ESC to resume\nPress M to return to menu");
        hintText_.setFillColor(sf::Color(180, 180, 180));
        hintText_.setPosition({120.f, 160.f}); // Фігурні дужки для sf::Vector2f
    }

    void PauseState::handleEvent(const sf::Event& event)
    {
        // Сучасна обробка подій натискання клавіш в SFML 3
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape)
            {
                stateMachine_.resume();
            }

            if (keyPressed->code == sf::Keyboard::Key::M)
            {
                stateMachine_.setState(controller::State::Menu);
            }
        }
    }

    void PauseState::update(float)
    {
        // intentionally empty (freeze gameplay)
    }

    void PauseState::render()
    {
        window_.clear(sf::Color(20, 20, 20));

        drawUI();

        window_.display();
    }

    void PauseState::drawUI()
    {
        window_.draw(titleText_);
        window_.draw(hintText_);
    }
}