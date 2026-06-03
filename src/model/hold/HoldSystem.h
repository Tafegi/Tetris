// src/model/hold/HoldSystem.h
#pragma once

#include "model/tetromino/Tetromino.h"
#include <optional>

/**
 * @brief Manages the hold slot (one piece can be stored / swapped).
 *
 * Per the Guideline, the player may only hold once per piece placement.
 * The lock is cleared when a new piece is spawned.
 */
class HoldSystem
{
public:
    HoldSystem() = default;

    /// Returns true if the hold was performed (false if locked this turn).
    bool hold(Tetromino& activePiece, Tetromino nextFromQueue);

    /// Allow holding again (call when a new piece spawns from the queue).
    void unlock() noexcept;

    void reset() noexcept;

    [[nodiscard]] bool                    hasHeld()    const noexcept;
    [[nodiscard]] const Tetromino&        getHeld()    const;
    [[nodiscard]] bool                    isLocked()   const noexcept { return m_locked; }

private:
    std::optional<Tetromino> m_held;
    bool                     m_locked{false};
};