#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "../model/statistics/StatisticsManager.h"

namespace view
{
    class StatisticsView
    {
    public:
        explicit StatisticsView(sf::RenderWindow& window);

        void render(const model::StatisticsManager& stats);

    private:
        void drawBackground();
        void drawTitle();
        void drawStats(const model::StatisticsManager& stats);

    private:
        sf::RenderWindow& window_;
        sf::Font font_;

        sf::Text title_;
        sf::Text statsText_;
    };
}