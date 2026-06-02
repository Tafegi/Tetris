#pragma once

#include <SFML/Graphics.hpp>

#include "../model/game/Game.h"
#include "AnimationSystem.h"

namespace view
{
    class GameView
    {
    public:
        GameView(sf::RenderWindow& window);

        void render(const model::Game& game);
        void update(float dt);

    private:
        void drawBoard(const model::Board& board);
        void drawPiece(const model::Tetromino& piece);
        void drawGhost(const model::Tetromino& piece, const model::Board& board);
        void drawUI(const model::Game& game);

        sf::Vector2f toScreen(int x, int y) const;

    private:
        sf::RenderWindow& window_;

        sf::RectangleShape blockShape_;
        sf::RectangleShape ghostShape_;

        AnimationSystem animationSystem_;
    };
}