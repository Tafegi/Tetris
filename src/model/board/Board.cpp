#include "Board.h"
#include <algorithm>

Board::Board()
{
    reset();
}

void Board::reset()
{
    for (auto& row : m_grid)
        row.fill(k_empty);
}

bool Board::isInBounds(int col, int row) const noexcept
{
    return col >= 0 && col < k_cols && row >= 0 && row < k_rows;
}

bool Board::isOccupied(int col, int row) const noexcept
{
    if (!isInBounds(col, row)) return true;
    return m_grid[row][col].a != 0;
}

sf::Color Board::getColor(int col, int row) const noexcept
{
    if (!isInBounds(col, row)) return k_empty;
    return m_grid[row][col];
}

bool Board::canPlace(const Tetromino& piece) const noexcept
{
    for (const auto& cell : piece.getAbsoluteCells())
    {
        if (cell.x < 0 || cell.x >= k_cols) return false;
        if (cell.y >= k_rows)               return false;
        // Allow cells above the board (during spawn)
        if (cell.y < 0)                     continue;
        if (isOccupied(cell.x, cell.y))     return false;
    }
    return true;
}

void Board::lockPiece(const Tetromino& piece)
{
    for (const auto& cell : piece.getAbsoluteCells())
    {
        if (!isInBounds(cell.x, cell.y)) continue;
        m_grid[cell.y][cell.x] = piece.getColor();
    }
}

int Board::clearFullRows()
{
    int cleared = 0;
    for (int row = k_rows - 1; row >= 0; )
    {
        bool full = std::all_of(m_grid[row].begin(), m_grid[row].end(),
                                [](const sf::Color& c){ return c.a != 0; });
        if (full)
        {
            for (int r = row; r > 0; --r)
                m_grid[r] = m_grid[r - 1];
            m_grid[0].fill(k_empty);
            ++cleared;
        }
        else
        {
            --row;
        }
    }
    return cleared;
}

Tetromino Board::hardDropPosition(const Tetromino& piece) const noexcept
{
    Tetromino dropped = piece;
    while (canPlace(dropped.moved(0, 1)))
        dropped = dropped.moved(0, 1);
    return dropped;
}