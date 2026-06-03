// src/view/MenuView.h
#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

enum class MenuOption { Play, Statistics, Quit };

class MenuView
{
public:
    explicit MenuView(sf::RenderWindow& window);
    void render();

    // Новий метод для перевірки кліку
    std::optional<MenuOption> handleClick(sf::Vector2i mousePos) const;

private:
    sf::Text makeText(const std::string& str, unsigned int size, sf::Color color);
    sf::RenderWindow& m_window;
    sf::Font          m_font;

    // Зберігаємо фізичні межі кнопок (прямокутники)
    sf::FloatRect m_playBounds;
    sf::FloatRect m_statsBounds;
    sf::FloatRect m_quitBounds;
};