#include "HoldSystem.h"

namespace model
{
    HoldSystem::HoldSystem()
        : usedThisTurn_(false),
          hasHeld_(false),
          heldType_(TetrominoType::I)
    {
    }

    void HoldSystem::reset()
    {
        usedThisTurn_ = false;
        hasHeld_ = false;
        heldType_ = TetrominoType::I;
    }

    // BUG FIX: was missing. Called by Game::spawnNext() so hold is
    // available once for every new piece (not locked after first use).
    void HoldSystem::resetTurn()
    {
        usedThisTurn_ = false;
    }

    bool HoldSystem::canHold() const noexcept
    {
        return !usedThisTurn_;
    }

    bool HoldSystem::hasHeld() const noexcept
    {
        return hasHeld_;
    }

    TetrominoType HoldSystem::heldType() const noexcept
    {
        return heldType_;
    }

    TetrominoType HoldSystem::hold(TetrominoType current)
    {
        if (usedThisTurn_)
            return current;

        usedThisTurn_ = true;

        if (!hasHeld_)
        {
            hasHeld_ = true;
            heldType_ = current;
            return current; // caller should spawn next from queue
        }

        TetrominoType swapped = heldType_;
        heldType_ = current;
        return swapped;
    }
}