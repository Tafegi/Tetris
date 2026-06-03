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
        title.setOrigin({b.size.x / 2.f, b.size.y / 2.f}); // SFML 3 fix
        title.setPosition({cx, 180.f});
    }
    m_window.draw(title);

    // ── Sub-title ──────────────────────────────────────
    auto sub = makeText("Classic Block Puzzle", 16, sf::Color(60, 120, 160));
    {
        const sf::FloatRect b = sub.getLocalBounds();
        sub.setOrigin({b.size.x / 2.f, b.size.y / 2.f}); // SFML 3 fix
        sub.setPosition({cx, 250.f});
    }
    m_window.draw(sub);

    // ── Menu options ───────────────────────────────────
    // Додаємо outBounds як параметр, щоб зберігати прямокутник тексту
    auto drawOption = [&](const std::string& text, float y, sf::Color color, sf::FloatRect& outBounds)
    {
        auto t = makeText(text, 22, color);
        const sf::FloatRect b = t.getLocalBounds();
        t.setOrigin({b.size.x / 2.f, b.size.y / 2.f}); // SFML 3 fix
        t.setPosition({cx, y});

        // Зберігаємо глобальні координати на екрані
        outBounds = t.getGlobalBounds();
        m_window.draw(t);
    };

    // Оновили текст і передаємо відповідні змінні для збереження границь
    drawOption("Click or ENTER to Play",    300.f, sf::Color(220, 220, 255), m_playBounds);
    drawOption("Click or S for Statistics", 345.f, sf::Color(160, 160, 190), m_statsBounds);
    drawOption("Click or ESC to Quit",      390.f, sf::Color(120, 120, 150), m_quitBounds);
}

// Новий метод, який повертає яку кнопку натиснуто
std::optional<MenuOption> MenuView::handleClick(sf::Vector2i mousePos) const
{
    // Перетворюємо координати миші у float для порівняння з FloatRect
    sf::Vector2f pos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (m_playBounds.contains(pos))  return MenuOption::Play;
    if (m_statsBounds.contains(pos)) return MenuOption::Statistics;
    if (m_quitBounds.contains(pos))  return MenuOption::Quit;

    return std::nullopt; // Клікнули в пусте місце
}