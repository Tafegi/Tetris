// src/view/GameOverView.cpp
#include "GameOverView.h"
#include "model/game/Game.h"
#include <string>

GameOverView::GameOverView(sf::RenderWindow& window)
    : m_window(window)
{
    if (!m_font.openFromFile("assets/fonts/Roboto-Regular.ttf"))
        (void)m_font.openFromFile("C:/Windows/Fonts/arial.ttf");
}

sf::Text GameOverView::makeText(const std::string& str, unsigned int size, sf::Color color)
{
    sf::Text t(m_font, str, size);
    t.setFillColor(color);
    return t;
}

void GameOverView::render(const Game& game)
{
    // Overlay
    sf::RectangleShape overlay(sf::Vector2f(
        static_cast<float>(m_window.getSize().x),
        static_cast<float>(m_window.getSize().y)));
    overlay.setFillColor(sf::Color(0, 0, 0, 175));
    m_window.draw(overlay);

    const float cx = static_cast<float>(m_window.getSize().x) / 2.f;
    const float cy = static_cast<float>(m_window.getSize().y) / 2.f;

    auto centered = [&](const std::string& str, unsigned int size,
                         sf::Color color, float y)
    {
        auto t = makeText(str, size, color);
        const sf::FloatRect b = t.getLocalBounds();
        t.setOrigin({b.position.x + b.size.x / 2.f,
                     b.position.y + b.size.y / 2.f});
        t.setPosition({cx, y});
        m_window.draw(t);
    };

    centered("GAME OVER",
             52, sf::Color(255, 80, 80),   cy - 80.f);
    centered("Score: " + std::to_string(game.getScore().getScore()),
             22, sf::Color(220, 220, 255), cy - 10.f);
    centered("Best:  " + std::to_string(game.getScore().getHighScore()),
             20, sf::Color(180, 180, 210), cy + 30.f);
    centered("Lines: " + std::to_string(game.getLevel().getTotalLines()),
             20, sf::Color(180, 180, 210), cy + 60.f);
    centered("Level: " + std::to_string(game.getLevel().getLevel()),
             20, sf::Color(180, 180, 210), cy + 90.f);

    centered("ENTER - New Game   S - Stats   ESC - Menu",
             14, sf::Color(120, 120, 150), cy + 150.f);
}