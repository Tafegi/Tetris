#pragma once

#include "model/tetromino/Tetromino.h"
#include <array>
#include <optional>

/**
 * @brief 10×20 playfield grid.
 *
 * The board stores placed-cell colors only (no piece logic).
 * Row 0 = top, row 19 = bottom (standard orientation).
 * Two hidden rows above (rows -2, -1) are handled via the spawn
 * offset; the internal array uses rows 0-21 with rows 0-1 hidden.
 */
class Board
{
public:
    static constexpr int k_cols       = 10;
    static constexpr int k_rows       = 22; // 20 visible + 2 hidden top rows
    static constexpr int k_hiddenRows = 2;  // rows 0-1 are above the visible ceiling

    Board();

    // ── Query ──────────────────────────────────────────────────────────────
    [[nodiscard]] bool              isOccupied(int col, int row) const noexcept;
    [[nodiscard]] bool              isInBounds(int col, int row) const noexcept;
    [[nodiscard]] sf::Color         getColor(int col, int row)   const noexcept;

    // True when the piece can occupy all four cells without conflict
    [[nodiscard]] bool              canPlace(const Tetromino& piece) const noexcept;

    // ── Mutation ───────────────────────────────────────────────────────────
    void                            lockPiece(const Tetromino& piece);

    // Clears all complete rows and returns how many were cleared
    [[nodiscard]] int               clearFullRows();

    void                            reset();

    // ── Ghost-piece helper ─────────────────────────────────────────────────
    // Returns the lowest valid drop position of 'piece'
    [[nodiscard]] Tetromino         hardDropPosition(const Tetromino& piece) const noexcept;

private:
    // Grid: [row][col].  sf::Color::Black == empty.
    std::array<std::array<sf::Color, k_cols>, k_rows> m_grid{};

    static constexpr sf::Color k_empty{0, 0, 0, 0}; // transparent = empty
};