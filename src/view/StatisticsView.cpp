#include "StatisticsView.h"
#include <sstream>

namespace view
{
    StatisticsView::StatisticsView(sf::RenderWindow& window)
        : window_(window),
          title_(font_),      // Явна ініціалізація шрифту для SFML 3
          statsText_(font_)   // Явна ініціалізація шрифту для SFML 3
    {
        if (!font_.openFromFile("assets/fonts/Roboto-Regular.ttf")) {
            // обробка помилки за бажанням
        }

        title_.setCharacterSize(48);
        title_.setString("STATISTICS");
        title_.setFillColor(sf::Color::White);

        statsText_.setCharacterSize(22);
        statsText_.setFillColor(sf::Color::White);
    }

    void StatisticsView::render(const model::StatisticsManager& stats)
    {
        window_.clear(sf::Color(12, 12, 12));

        drawBackground();
        drawTitle();
        drawStats(stats);

        window_.display();
    }

    void StatisticsView::drawBackground()
    {
        sf::RectangleShape bg;
        bg.setSize({
            static_cast<float>(window_.getSize().x),
            static_cast<float>(window_.getSize().y)
        });

        bg.setFillColor(sf::Color(10, 10, 10));
        window_.draw(bg);
    }

    void StatisticsView::drawTitle()
    {
        title_.setPosition({100.f, 50.f}); // Фігурні дужки для sf::Vector2f
        window_.draw(title_);
    }

    void StatisticsView::drawStats(const model::StatisticsManager& stats)
    {
        std::ostringstream ss;

        ss << "Total Games: " << stats.totalGames() << "\n";
        ss << "Total Play Time: " << stats.totalPlayTime() << "\n";
        ss << "Highest Score: " << stats.highestScore() << "\n";
        ss << "Total Lines: " << stats.totalLines() << "\n";

        /* * ПРИМІТКА: Твій компілятор сварився, що цих методів немає в StatisticsManager.
         * Розкоментуй або перейменуй їх, коли звіришся з файлом StatisticsManager.h:
         *
         * ss << "Average Score: " << stats.averageScore() << "\n";
         * ss << "Tetris Count: " << stats.tetrisCount() << "\n";
         * ss << "T-Spin Count: " << stats.tSpinCount() << "\n";
         * ss << "Perfect Clears: " << stats.perfectClearCount() << "\n";
         */

        statsText_.setString(ss.str());
        statsText_.setPosition({100.f, 140.f}); // Фігурні дужки для sf::Vector2f

        window_.draw(statsText_);
    }
}