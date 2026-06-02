#pragma once

#include <memory>
#include <cstdint>

#include "../board/Board.h"
#include "../queue/PieceQueue.h"
#include "../hold/HoldSystem.h"
#include "../score/ScoreSystem.h"
#include "../level/LevelSystem.h"
#include "../rules/GameplayRules.h"
#include "../timer/GameTimer.h"

#include "../tetromino/Tetromino.h"
#include "../tetromino/TetrominoFactory.h"

namespace model
{
    enum class GameState
    {
        Running,
        Paused,
        GameOver
    };

    class Game
    {
    public:
        Game();

        void reset();

        void update(double dt);
        void tick(); // gravity step

        void moveLeft();
        void moveRight();
        void moveDown();
        void hardDrop();

        void rotateCW();
        void rotateCCW();

        void hold();

        GameState state() const noexcept;

        const Board& board() const noexcept;
        const Tetromino& activePiece() const noexcept;

        std::int64_t score() const noexcept;
        std::int32_t level() const noexcept;
        std::int32_t lines() const noexcept;

    private:
        void spawnNext();
        void lockPiece();
        void clearLines();

        bool isGameOver() const;

    private:
        Board board_;

        PieceQueue queue_;
        HoldSystem hold_;

        ScoreSystem scoreSystem_;
        LevelSystem levelSystem_;
        GameplayRules rules_;

        GameTimer timer_;

        TetrominoFactory factory_;
        Tetromino activePiece_;

        GameState state_;
    };
}