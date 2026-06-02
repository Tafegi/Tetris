#include "LeaderboardState.h"
#include <sstream>

namespace state
{
    LeaderboardState::LeaderboardState(sf::RenderWindow& window,
                                       controller::StateMachine& stateMachine,
                                       const model::HighScoreManager& highScores)
        : window_(window)
        , stateMachine_(stateMachine)
        , highScores_(highScores)
        , titleText_(font_) // Явна ініціалізація шрифту для SFML 3
        , listText_(font_)  // Явна ініціалізація шрифту для SFML 3
    {
        if (!font_.openFromFile("assets/fonts/Roboto-Regular.ttf")) {
            // обробка помилки за бажанням
        }

        titleText_.setCharacterSize(48);
        titleText_.setString("LEADERBOARD");
        titleText_.setFillColor(sf::Color::Yellow);
        titleText_.setPosition({100.f, 60.f}); // Фігурні дужки для sf::Vector2f

        listText_.setCharacterSize(22);
        listText_.setFillColor(sf::Color::White);
        listText_.setPosition({100.f, 140.f}); // Фігурні дужки для sf::Vector2f
    }

    void LeaderboardState::handleEvent(const sf::Event& event)
    {
        // Сучасний синтаксис подій SFML 3
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape)
            {
                stateMachine_.setState(controller::State::Menu);
            }
        }
    }

    void LeaderboardState::update(float)
    {
        std::ostringstream ss;

        // Виправлено: тепер викликаємо точний метод з твого HighScoreManager.h
        const auto& records = highScores_.entries();

        int rank = 1;

        for (const auto& e : records)
        {
            ss << rank++ << ". "
               << e.playerName << " - "
               << e.score << " pts\n";
        }

        listText_.setString(ss.str());
    }

    void LeaderboardState::render()
    {
        window_.clear(sf::Color(15, 15, 15));

        drawUI();

        window_.display();
    }

    void LeaderboardState::drawUI()
    {
        window_.draw(titleText_);
        window_.draw(listText_);
    }
}