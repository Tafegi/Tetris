// src/view/MenuView.h
#pragma once
#include <SFML/Graphics.hpp>

class MenuView
{
public:
    explicit MenuView(sf::RenderWindow& window);
    void render();

private:
    sf::Text makeText(const std::string& str, unsigned int size, sf::Color color);
    sf::RenderWindow& m_window;
    sf::Font          m_font;
};