#pragma once
#include <SFML/Graphics.hpp>

class StatisticsManager;
class ScoreSystem;
class LevelSystem;

class StatisticsView
{
public:
    explicit StatisticsView(sf::RenderWindow& window);

    void render(const StatisticsManager& stats,
                const ScoreSystem&       score,
                const LevelSystem&       level);

private:
    sf::Text makeText(const std::string& str, unsigned int size, sf::Color color);
    sf::RenderWindow& m_window;
    sf::Font          m_font;
};