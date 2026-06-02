#include "GameOverView.h"
#include <sstream>

namespace view
{
    GameOverView::GameOverView(sf::RenderWindow& window)
        : window_(window),
          titleText_(font_),  // Ініціалізація шрифту для SFML 3
          statsText_(font_),  // Ініціалізація шрифту для SFML 3
          promptText_(font_)  // Ініціалізація шрифту для SFML 3
    {
        if (!font_.openFromFile("assets/fonts/Roboto-Regular.ttf")) {
            // обробка помилки за бажанням
        }

        titleText_.setCharacterSize(48);
        statsText_.setCharacterSize(24);
        promptText_.setCharacterSize(20);

        titleText_.setFillColor(sf::Color::Red);
        statsText_.setFillColor(sf::Color::White);
        promptText_.setFillColor(sf::Color::Yellow);

        titleText_.setString("GAME OVER");
    }

    void GameOverView::render(const model::Game& game, const std::string& playerName)
    {
        window_.clear(sf::Color(10, 10, 10));

        drawBackground();
        drawTitle();
        drawStats(game);
        drawPrompt(playerName);

        window_.display();
    }

    void GameOverView::drawBackground()
    {
        sf::RectangleShape bg;
        bg.setSize({
            static_cast<float>(window_.getSize().x),
            static_cast<float>(window_.getSize().y)
        });

        bg.setFillColor(sf::Color(0, 0, 0, 200));
        window_.draw(bg);
    }

    void GameOverView::drawTitle()
    {
        titleText_.setPosition({100.f, 50.f}); // Загортаємо в {} для sf::Vector2f
        window_.draw(titleText_);
    }

    void GameOverView::drawStats(const model::Game& game)
    {
        std::ostringstream ss;

        ss << "Score: " << game.score() << "\n";
        ss << "Level: " << game.level() << "\n";
        ss << "Lines: " << game.lines();

        statsText_.setString(ss.str());
        statsText_.setPosition({100.f, 150.f}); // Загортаємо в {}

        window_.draw(statsText_);
    }

    void GameOverView::drawPrompt(const std::string& playerName)
    {
        promptText_.setString("Press Enter to save score: " + playerName);
        promptText_.setPosition({100.f, 300.f}); // Загортаємо в {}

        window_.draw(promptText_);
    }
}