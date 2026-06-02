#include "GameOverView.h"
#include <sstream>

namespace view
{
    static void drawButton(sf::RenderWindow& window, const sf::Font& font,
                           const std::string& text, sf::FloatRect rect, bool hover)
    {
        sf::RectangleShape box(rect.size);
        box.setPosition(rect.position);
        box.setFillColor(hover ? sf::Color(60, 60, 120) : sf::Color(30, 30, 70));
        box.setOutlineThickness(2.f);
        box.setOutlineColor(hover ? sf::Color(140, 140, 255) : sf::Color(60, 60, 120));
        window.draw(box);

        sf::Text label(font);
        label.setCharacterSize(22);
        label.setFillColor(sf::Color::White);
        label.setString(text);
        auto lb = label.getLocalBounds();
        label.setOrigin({lb.size.x / 2.f, lb.size.y / 2.f});
        label.setPosition({rect.position.x + rect.size.x / 2.f,
                           rect.position.y + rect.size.y / 2.f});
        window.draw(label);
    }

    GameOverView::GameOverView(sf::RenderWindow& window)
        : window_(window),
          titleText_(font_),
          statsText_(font_),
          promptText_(font_)
    {
        font_.openFromFile("assets/fonts/Roboto-Regular.ttf");

        titleText_.setCharacterSize(56);
        titleText_.setString("GAME OVER");
        titleText_.setFillColor(sf::Color(240, 60, 60));

        statsText_.setCharacterSize(24);
        statsText_.setFillColor(sf::Color::White);

        promptText_.setCharacterSize(18);
        promptText_.setFillColor(sf::Color(180, 180, 200));
    }

    sf::FloatRect GameOverView::playAgainRect() const
    {
        return sf::FloatRect({100.f, 400.f}, {200.f, 50.f});
    }

    sf::FloatRect GameOverView::mainMenuRect() const
    {
        return sf::FloatRect({320.f, 400.f}, {200.f, 50.f});
    }

    void GameOverView::render(const model::Game& game, const std::string& playerName)
    {
        window_.clear(sf::Color(10, 5, 5));
        drawBackground();
        drawTitle();
        drawStats(game);
        drawPrompt(playerName);
        drawButtons();
        window_.display();
    }

    void GameOverView::drawBackground()
    {
        sf::RectangleShape bg;
        bg.setSize({(float)window_.getSize().x, (float)window_.getSize().y});
        bg.setFillColor(sf::Color(12, 5, 8));
        window_.draw(bg);
    }

    void GameOverView::drawTitle()
    {
        auto bounds = titleText_.getLocalBounds();
        titleText_.setOrigin({bounds.size.x / 2.f, 0.f});
        titleText_.setPosition({window_.getSize().x / 2.f, 80.f});
        window_.draw(titleText_);
    }

    void GameOverView::drawStats(const model::Game& game)
    {
        std::ostringstream ss;
        ss << "Score : " << game.score() << "\n"
           << "Level : " << game.level() << "\n"
           << "Lines : " << game.lines();
        statsText_.setString(ss.str());
        statsText_.setPosition({100.f, 200.f});
        window_.draw(statsText_);
    }

    void GameOverView::drawPrompt(const std::string& playerName)
    {
        (void)playerName;
        promptText_.setString("Press Enter or click Play Again to restart\nPress Escape or click Main Menu to go back");
        promptText_.setPosition({100.f, 340.f});
        window_.draw(promptText_);
    }

    void GameOverView::drawButtons()
    {
        sf::Vector2i mouse = sf::Mouse::getPosition(window_);
        sf::Vector2f mf((float)mouse.x, (float)mouse.y);

        drawButton(window_, font_, "Play Again", playAgainRect(),
                   playAgainRect().contains(mf));
        drawButton(window_, font_, "Main Menu",  mainMenuRect(),
                   mainMenuRect().contains(mf));
    }

    bool GameOverView::handleMouseClick(sf::Vector2i pos,
                                        bool& outPlayAgain,
                                        bool& outMainMenu)
    {
        sf::Vector2f pf((float)pos.x, (float)pos.y);
        outPlayAgain = playAgainRect().contains(pf);
        outMainMenu  = mainMenuRect().contains(pf);
        return outPlayAgain || outMainMenu;
    }
}