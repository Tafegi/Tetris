#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

#include "../model/game/Game.h"
#include "AnimationSystem.h"

namespace view
{
    class GameView
    {
    public:
        explicit GameView(sf::RenderWindow& window);

        void render(const model::Game& game);
        void update(float dt);

    private:
        void drawBoardBorder();
        void drawBoard(const model::Board& board);
        void drawPiece(const model::Tetromino& piece);
        void drawGhost(const model::Tetromino& piece, const model::Board& board);
        void drawHUD(const model::Game& game);
        void drawMiniPiece(model::TetrominoType type, float px, float py);

        sf::Vector2f toScreen(int x, int y) const;

    private:
        sf::RenderWindow& window_;
        sf::Font font_;

        sf::RectangleShape blockShape_;
        sf::RectangleShape ghostShape_;

        AnimationSystem animationSystem_;
    };
}