#include "PlayingState.h"
#include <sstream>

namespace state
{
    PlayingState::PlayingState(sf::RenderWindow& window,
                               controller::StateMachine& stateMachine,
                               model::Game& game,
                               controller::InputController& input)
        : window_(window)
        , stateMachine_(stateMachine)
        , game_(game)
        , input_(input)
        , gameView_(window)  // Ініціалізуємо GameView
        , hudText_(font_)    // Явна ініціалізація шрифту для SFML 3
    {
        if (!font_.openFromFile("assets/fonts/Roboto-Regular.ttf")) {
            // обробка помилки за бажанням
        }

        hudText_.setCharacterSize(20);
        hudText_.setFillColor(sf::Color::White);
        hudText_.setPosition({10.f, 10.f}); // Фігурні дужки для sf::Vector2f
    }

    void PlayingState::handleEvent(const sf::Event& event)
    {
        input_.process(event, stateMachine_, game_);

        // Сучасний синтаксис подій SFML 3
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape)
            {
                stateMachine_.setState(controller::State::Pause);
            }
        }
    }

    void PlayingState::update(float dt)
    {
        input_.update(dt, game_);
        game_.update(dt);

        // Виправлено: перевіряємо статус гри через відкритий енум GameState
        if (game_.state() == model::GameState::GameOver)
        {
            stateMachine_.setState(controller::State::GameOver);
        }
    }

    void PlayingState::render()
    {
        window_.clear(sf::Color(0, 0, 0));

        // Виправлено: малюємо ігрове поле через спеціалізований GameView
        gameView_.render(game_);

        drawUI();

        window_.display();
    }

    void PlayingState::drawUI()
    {
        std::ostringstream ss;

        // Виправлено: замість linesCleared() викликаємо lines()
        ss << "Score: " << game_.score() << "\n"
           << "Level: " << game_.level() << "\n"
           << "Lines: " << game_.lines();

        hudText_.setString(ss.str());

        window_.draw(hudText_);
    }
}