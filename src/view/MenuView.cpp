// src/view/MenuView.cpp
#include "MenuView.h"

MenuView::MenuView(sf::RenderWindow& window)
    : m_window(window)
{
    if (!m_font.openFromFile("assets/fonts/Roboto-Regular.ttf"))
        (void)m_font.openFromFile("C:/Windows/Fonts/arial.ttf");
}

sf::Text MenuView::makeText(const std::string& str, unsigned int size, sf::Color color)
{
    sf::Text t(m_font, str, size);
    t.setFillColor(color);
    return t;
}

void MenuView::render()
{
    const float cx = static_cast<float>(m_window.getSize().x) / 2.f;

    // ── Title ──────────────────────────────────────────
    auto title = makeText("TETRIS", 72, sf::Color(80, 200, 255));
    title.setStyle(sf::Text::Bold);
    {
        const sf::FloatRect b = title.getLocalBounds();
        title.setOrigin({b.position.x + b.size.x / 2.f,
                          b.position.y + b.size.y / 2.f});
        title.setPosition({cx, 180.f});
    }
    m_window.draw(title);

    // ── Sub-title ──────────────────────────────────────
    auto sub = makeText("Classic Block Puzzle", 16, sf::Color(60, 120, 160));
    {
        const sf::FloatRect b = sub.getLocalBounds();
        sub.setOrigin({b.position.x + b.size.x / 2.f,
                        b.position.y + b.size.y / 2.f});
        sub.setPosition({cx, 250.f});
    }
    m_window.draw(sub);

    // ── Menu options ───────────────────────────────────
    auto drawOption = [&](const std::string& text, float y, sf::Color color)
    {
        auto t = makeText(text, 22, color);
        const sf::FloatRect b = t.getLocalBounds();
        t.setOrigin({b.position.x + b.size.x / 2.f,
                     b.position.y + b.size.y / 2.f});
        t.setPosition({cx, y});

        m_window.draw(t);
    };

    drawOption("Press ENTER to Play",    300.f, sf::Color(220, 220, 255));
    drawOption("Press S for Statistics", 345.f, sf::Color(160, 160, 190));
    drawOption("Press ESC to Quit",      390.f, sf::Color(120, 120, 150));
}