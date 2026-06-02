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
    enum class GameState { Running, Paused, GameOver };

    class Game
    {
    public:
        Game();

        void reset();
        void update(float dt);   // BUG FIX: was double, all callers pass float
        void tick();

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
        const PieceQueue& queue() const noexcept;

        std::int64_t score() const noexcept;
        std::int32_t level() const noexcept;
        std::int32_t lines() const noexcept;

        TetrominoType heldPiece() const noexcept;
        bool hasHeldPiece() const noexcept;

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
        double gravityAccumulator_{0.0};  // BUG FIX: was missing
        TetrominoFactory factory_;
        Tetromino activePiece_;
        GameState state_;
    };
}