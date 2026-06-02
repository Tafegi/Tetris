#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

#include "../model/game/Game.h"
#include "../model/highscore/HighScoreManager.h"

namespace view
{
    class GameOverView
    {
    public:
        explicit GameOverView(sf::RenderWindow& window);

        // callback: called when player confirms name to save score
        void render(const model::Game& game, const std::string& playerName);

        // returns true if a clickable button was hit
        bool handleMouseClick(sf::Vector2i pos,
                              bool& outPlayAgain,
                              bool& outMainMenu);

    private:
        void drawBackground();
        void drawTitle();
        void drawStats(const model::Game& game);
        void drawButtons();
        void drawPrompt(const std::string& playerName);

        sf::FloatRect playAgainRect() const;
        sf::FloatRect mainMenuRect() const;

    private:
        sf::RenderWindow& window_;
        sf::Font font_;
        sf::Text titleText_;
        sf::Text statsText_;
        sf::Text promptText_;
    };
}