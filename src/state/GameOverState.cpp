#include "GameOverState.h"
#include <sstream>

namespace state
{
    GameOverState::GameOverState(sf::RenderWindow& window,
                                 controller::StateMachine& stateMachine,
                                 const model::Game& game)
        : window_(window)
        , stateMachine_(stateMachine)
        , game_(game)
        , titleText_(font_) // Явна ініціалізація шрифту для SFML 3
        , statsText_(font_) // Явна ініціалізація шрифту для SFML 3
    {
        if (!font_.openFromFile("assets/fonts/Roboto-Regular.ttf")) {
            // обробка помилки за бажанням
        }

        titleText_.setCharacterSize(48);
        titleText_.setString("GAME OVER");
        titleText_.setFillColor(sf::Color::Red);
        titleText_.setPosition({100.f, 80.f}); // Фігурні дужки для sf::Vector2f

        statsText_.setCharacterSize(22);
        statsText_.setFillColor(sf::Color::White);
        statsText_.setPosition({100.f, 160.f}); // Фігурні дужки для sf::Vector2f
    }

    void GameOverState::handleEvent(const sf::Event& event)
    {
        // Сучасний синтаксис подій SFML 3
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Enter)
            {
                stateMachine_.setState(controller::State::EnterName);
            }

            if (keyPressed->code == sf::Keyboard::Key::Escape)
            {
                stateMachine_.setState(controller::State::Menu);
            }
        }
    }

    void GameOverState::update(float)
    {
        std::ostringstream ss;
        // Виправлено: використовуємо правильні відкриті геттери моделі Game
        ss << "Score: " << game_.score() << "\n"
           << "Level: " << game_.level() << "\n"
           << "Lines: " << game_.lines() << "\n";

        statsText_.setString(ss.str());
    }

    void GameOverState::render()
    {
        window_.clear(sf::Color(15, 5, 5));
        drawUI();
        window_.display();
    }

    void GameOverState::drawUI()
    {
        window_.draw(titleText_);
        window_.draw(statsText_);
    }
}