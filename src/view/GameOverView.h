#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "../model/game/Game.h"

namespace view
{
    class GameOverView
    {
    public:
        explicit GameOverView(sf::RenderWindow& window);

        void render(const model::Game& game, const std::string& playerName);

    private:
        void drawBackground();
        void drawTitle();
        void drawStats(const model::Game& game);
        void drawPrompt(const std::string& playerName);

    private:
        sf::RenderWindow& window_;

        sf::Font font_;

        sf::Text titleText_;
        sf::Text statsText_;
        sf::Text promptText_;
    };
}