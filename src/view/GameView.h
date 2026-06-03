// src/view/GameView.h
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

// Forward declarations – keep view headers thin
class Game;
class Tetromino;
class Board;

/**
 * @brief Renders the main game screen: board, active piece, ghost, HUD panels.
 *
 * Owns the font and all reusable sf:: objects; rebuilds nothing per-frame
 * unless state changes.  All measurements are in pixels, derived from
 * the single constant k_cellSize.
 */
class GameView
{
public:
    explicit GameView(sf::RenderWindow& window);

    void render(const Game& game);

private:
    // ── Drawing helpers ────────────────────────────────────────────────────
    void drawBoard       (const Game& game);
    void drawActivePiece (const Game& game);
    void drawGhostPiece  (const Game& game);
    void drawHUD         (const Game& game);
    void drawNextPanel   (const Game& game);
    void drawHoldPanel   (const Game& game);
    void drawPausedOverlay();

    void drawCell(int col, int row, sf::Color color, float alpha = 1.0f);
    void drawPiecePreview(const Tetromino& piece, float originX, float originY);

    sf::RenderWindow& m_window;
    sf::Font          m_font;

    // Layout constants
    static constexpr float k_cellSize     = 30.0f;
    static constexpr float k_boardLeft    = 200.0f;  // px from window left
    static constexpr float k_boardTop     = 20.0f;
    static constexpr int   k_visibleRows  = 20;
    static constexpr int   k_hiddenRows   = 2;

    sf::RectangleShape m_cellShape;
    sf::RectangleShape m_boardBorder;
};