#pragma once

#include "../types/TetrominoType.h"

namespace model
{
    class HoldSystem
    {
    public:
        HoldSystem();

        // returns true if swap happened
        bool canHold() const noexcept;

        // performs hold swap
        // currentPiece becomes held, returns previous held (if any)
        TetrominoType hold(TetrominoType current);

        void reset();

        bool hasHeld() const noexcept;

    private:
        bool usedThisTurn_;

        bool hasHeld_;
        TetrominoType heldType_;
    };
}