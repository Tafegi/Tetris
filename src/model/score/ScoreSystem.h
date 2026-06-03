// src/model/score/ScoreSystem.h
#pragma once
#include <cstdint>

/**
 * @brief Classic Tetris scoring (Guideline style).
 *
 * Points per clear: Single=100, Double=300, Triple=500, Tetris=800.
 * All values are multiplied by the current level.
 * A soft-drop adds 1 pt / cell; hard-drop adds 2 pts / cell.
 */
class ScoreSystem
{
public:
    ScoreSystem() = default;

    void addClearPoints(int linesCleared, int level) noexcept;
    void addSoftDrop(int cells) noexcept;
    void addHardDrop(int cells) noexcept;

    [[nodiscard]] uint64_t getScore()    const noexcept { return m_score;    }
    [[nodiscard]] uint64_t getHighScore()const noexcept { return m_highScore; }

    void reset() noexcept;

private:
    uint64_t m_score{0};
    uint64_t m_highScore{0};
};