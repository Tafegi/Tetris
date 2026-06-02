#pragma once

#include <SFML/Graphics.hpp>

namespace view
{
    class PauseView
    {
    public:
        explicit PauseView(sf::RenderWindow& window);

        void render();

    private:
        void drawOverlay();
        void drawTitle();
        void drawHint();

    private:
        sf::RenderWindow& window_;

        sf::Font font_;

        sf::Text titleText_;
        sf::Text hintText_;
    };
}