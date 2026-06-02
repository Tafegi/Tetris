#include "GameplayRules.h"
#include <algorithm>

namespace model
{
    GameplayRules::GameplayRules() = default;

    bool GameplayRules::canMove(const Tetromino& piece, const Board& board, int dx, int dy) const
    {
        Tetromino test = piece;
        test.move(dx, dy);

        return !board.isCollision(test);
    }

    bool GameplayRules::canRotate(const Tetromino& piece, const Board& board, Rotation newRotation) const
    {
        (void)newRotation; // Глушимо помилку unused parameter для -Werror

        Tetromino test = piece;

        // simulate rotation by applying step-by-step
        test.rotateClockwise(); // simplified placeholder

        return !board.isCollision(test);
    }

    bool GameplayRules::isCornerBlocked(const Board& board, int x, int y) const
    {
        // simplified T-spin corner check placeholder
        int blocked = 0;

        // Перевіряємо поле .occupied нашої структури Cell
        if (board.grid()[y - 1][x].occupied) ++blocked;
        if (board.grid()[y + 1][x].occupied) ++blocked;
        if (board.grid()[y][x - 1].occupied) ++blocked;
        if (board.grid()[y][x + 1].occupied) ++blocked;

        return blocked >= 3;
    }

    bool GameplayRules::isTSpin(const Tetromino& piece, const Board& board) const
    {
        const auto pos = piece.position();

        // T-spin only applies to T piece
        if (piece.type() != TetrominoType::T)
            return false;

        return isCornerBlocked(board, pos.x, pos.y);
    }

    bool GameplayRules::isMiniTSpin(const Tetromino& piece, const Board& board) const
    {
        // simplified version (real SRS would be more complex)
        const auto pos = piece.position();

        if (piece.type() != TetrominoType::T)
            return false;

        return !isCornerBlocked(board, pos.x, pos.y);
    }

    bool GameplayRules::isPerfectClear(const Board& board) const
    {
        const auto& grid = board.grid();

        for (const auto& row : grid)
        {
            // Ітеруємо як об'єкти Cell, а не int
            for (const auto& cell : row)
            {
                if (cell.occupied)
                    return false;
            }
        }

        return true;
    }

    ScoreEvent GameplayRules::evaluateClearEvent(
        int linesCleared,
        bool tSpin,
        bool miniTSpin,
        bool perfectClear) const
    {
        if (perfectClear)
            return ScoreEvent::PerfectClear;

        if (tSpin)
        {
            switch (linesCleared)
            {
                case 1: return ScoreEvent::TSpinSingle;
                case 2: return ScoreEvent::TSpinDouble;
                case 3: return ScoreEvent::TSpinTriple;
                default: return ScoreEvent::TSpinMini;
            }
        }

        if (miniTSpin)
            return ScoreEvent::TSpinMini;

        switch (linesCleared)
        {
            case 1: return ScoreEvent::Single;
            case 2: return ScoreEvent::Double;
            case 3: return ScoreEvent::Triple;
            case 4: return ScoreEvent::Tetris;
            default: return ScoreEvent::Single;
        }
    }
}