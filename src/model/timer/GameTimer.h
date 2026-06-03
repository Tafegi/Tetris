// src/model/timer/GameTimer.h
#pragma once

/**
 * @brief Accumulates elapsed time and fires a callback when an interval elapses.
 *
 * Used for the gravity timer (auto-drop) and lock-delay timer.
 */
class GameTimer
{
public:
    explicit GameTimer(float interval = 1.0f) noexcept;

    void  setInterval(float seconds) noexcept;
    void  reset()                    noexcept;

    /// Advance the timer by deltaTime; returns true each time it fires.
    bool  update(float deltaTime)    noexcept;

    [[nodiscard]] float getInterval()    const noexcept { return m_interval; }
    [[nodiscard]] float getAccumulated() const noexcept { return m_accumulated; }

private:
    float m_interval{1.0f};
    float m_accumulated{0.0f};
};