// src/view/GameOverView.h
#pragma once
#include <SFML/Graphics.hpp>

class Game;

class GameOverView
{
public:
    explicit GameOverView(sf::RenderWindow& window);
    void render(const Game& game);

private:
    sf::Text makeText(const std::string& str, unsigned int size, sf::Color color);
    sf::RenderWindow& m_window;
    sf::Font          m_font;
};