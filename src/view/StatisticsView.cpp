#include "StatisticsView.h"
#include "model/statistics/StatisticsManager.h"
#include "model/score/ScoreSystem.h"
#include "model/level/LevelSystem.h"
#include "model/tetromino/Tetromino.h"
#include <string>
#include <array>

StatisticsView::StatisticsView(sf::RenderWindow& window)
    : m_window(window)
{
    if (!m_font.openFromFile("assets/fonts/Roboto-Regular.ttf"))
        (void)m_font.openFromFile("C:/Windows/Fonts/arial.ttf");
}

sf::Text StatisticsView::makeText(const std::string& str, unsigned int size, sf::Color color)
{
    sf::Text t(m_font, str, size);
    t.setFillColor(color);
    return t;
}

void StatisticsView::render(const StatisticsManager& stats,
                              const ScoreSystem&       score,
                              const LevelSystem&       level)
{
    const float cx = static_cast<float>(m_window.getSize().x) / 2.f;
    float y = 60.f;

    auto draw = [&](const std::string& str, unsigned int size, sf::Color color)
    {
        auto t = makeText(str, size, color);
        const sf::FloatRect b = t.getLocalBounds();
        t.setOrigin({b.position.x + b.size.x / 2.f, b.position.y});
        t.setPosition({cx, y});
        m_window.draw(t);
        y += static_cast<float>(size) + 10.f;
    };

    draw("STATISTICS",  36, sf::Color(80, 200, 255));
    y += 10.f;
    draw("High Score : " + std::to_string(score.getHighScore()), 20, sf::Color(220, 220, 255));
    draw("Level      : " + std::to_string(level.getLevel()),     18, sf::Color(190, 190, 220));
    draw("Total Lines: " + std::to_string(level.getTotalLines()),18, sf::Color(190, 190, 220));
    y += 10.f;

    draw("--- Line Clears ---", 16, sf::Color(100, 100, 130));
    constexpr std::array<const char*, 4> clearNames{"Single","Double","Triple","Tetris"};
    for (int i = 1; i <= 4; ++i)
        draw(std::string(clearNames[i-1]) + " : " +
             std::to_string(stats.getLineClearCount(i)),
             16, sf::Color(170, 170, 200));

    y += 10.f;

    draw("--- Pieces ---", 16, sf::Color(100, 100, 130));
    constexpr std::array<TetrominoType, 7> types{
        TetrominoType::I, TetrominoType::J, TetrominoType::L, TetrominoType::O,
        TetrominoType::S, TetrominoType::T, TetrominoType::Z};

    constexpr std::array<const char*, 7> names{"I","J","L","O","S","T","Z"};
    for (int i = 0; i < 7; ++i)
        draw(std::string(names[i]) + " : " +
             std::to_string(stats.getPieceCount(types[i])),
             16, sf::Color(170, 170, 200));

    y += 20.f;
    draw("Press ESC or ENTER to return", 14, sf::Color(90, 90, 110));
}