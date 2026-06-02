#pragma once

#include "../types/Rotation.h"
#include "../tetromino/Tetromino.h"
#include "../board/Board.h"
#include "../types/ScoreEvent.h"

#include <optional>

namespace model
{
    class GameplayRules
    {
    public:
        GameplayRules();

        bool canMove(const Tetromino& piece, const Board& board, int dx, int dy) const;
        bool canRotate(const Tetromino& piece, const Board& board, Rotation newRotation) const;

        bool isTSpin(const Tetromino& piece, const Board& board) const;
        bool isMiniTSpin(const Tetromino& piece, const Board& board) const;

        bool isPerfectClear(const Board& board) const;

        ScoreEvent evaluateClearEvent(int linesCleared, bool tSpin, bool miniTSpin, bool perfectClear) const;

    private:
        bool isCornerBlocked(const Board& board, int x, int y) const;
    };
}