#pragma once

#include "../types/TetrominoType.h"

namespace model
{
    class HoldSystem
    {
    public:
        HoldSystem();

        // Returns true if hold is allowed this piece
        bool canHold() const noexcept;

        // Performs hold: returns the type that should become active.
        // If nothing was held yet, stores current and returns current
        // (caller should spawn next from queue instead).
        TetrominoType hold(TetrominoType current);

        // BUG FIX: must be called each time a new piece spawns
        // so the player can hold once per piece (not once per game)
        void resetTurn();

        void reset();

        bool hasHeld() const noexcept;
        TetrominoType heldType() const noexcept;

    private:
        bool usedThisTurn_;
        bool hasHeld_;
        TetrominoType heldType_;
    };
}