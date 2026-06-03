#pragma once

#include "model/board/Board.h"
#include "model/hold/HoldSystem.h"
#include "model/level/LevelSystem.h"
#include "model/queue/PieceQueue.h"
#include "model/score/ScoreSystem.h"
#include "model/statistics/StatisticsManager.h"
#include "model/tetromino/Tetromino.h"
#include "model/timer/GameTimer.h"

/**
 * @brief Central game-logic façade.  Pure model – zero rendering code.
 *
 * Owns all sub-systems and exposes a clean action API that the
 * Controller calls in response to player input or timer ticks.
 */
class Game
{
public:
    Game();

    // ── Lifecycle ──────────────────────────────────────────────────────────
    void start();
    void reset();

    // ── Per-frame update (called with frame delta in seconds) ──────────────
    void update(float deltaTime);

    // ── Player actions ─────────────────────────────────────────────────────
    void moveLeft();
    void moveRight();
    void softDrop();
    void hardDrop();
    void rotateCW();
    void rotateCCW();
    void holdPiece();
    void togglePause();

    // ── Read-only access to sub-systems (for the View) ────────────────────
    [[nodiscard]] const Board&             getBoard()      const noexcept { return m_board; }
    [[nodiscard]] const Tetromino&         getActivePiece()const noexcept { return m_active; }
    [[nodiscard]] Tetromino                getGhostPiece() const noexcept;
    [[nodiscard]] const PieceQueue&        getQueue()      const noexcept { return m_queue; }
    [[nodiscard]] const HoldSystem&        getHold()       const noexcept { return m_hold; }
    [[nodiscard]] const ScoreSystem&       getScore()      const noexcept { return m_score; }
    [[nodiscard]] const LevelSystem&       getLevel()      const noexcept { return m_level; }
    [[nodiscard]] const StatisticsManager& getStats()      const noexcept { return m_stats; }

    [[nodiscard]] bool isGameOver() const noexcept { return m_gameOver; }
    [[nodiscard]] bool isPaused()   const noexcept { return m_paused;   }

private:
    // Spawn the next piece from the queue onto the board.
    // Returns false if the spawn position is blocked (game over).
    bool spawnNext();

    // Try to move the active piece; returns true on success.
    bool tryMove(const Tetromino& candidate);

    // Try SRS rotation with wall-kicks.
    bool tryRotate(bool clockwise);

    // Lock the active piece, clear rows, and spawn the next.
    void lockAndSpawn();

    // ── Sub-systems ────────────────────────────────────────────────────────
    Board             m_board;
    PieceQueue        m_queue;
    HoldSystem        m_hold;
    ScoreSystem       m_score;
    LevelSystem       m_level;
    StatisticsManager m_stats;

    Tetromino         m_active;
    GameTimer         m_gravityTimer;

    // Lock-delay: piece locks after ~0.5 s sitting on the floor
    GameTimer         m_lockTimer;
    bool              m_onGround{false};

    bool              m_gameOver{false};
    bool              m_paused{false};
    bool              m_started{false};
};