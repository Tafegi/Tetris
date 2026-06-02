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

    bool HoldSystem::canHold() const noexcept
    {
        return !usedThisTurn_;
    }

    bool HoldSystem::hasHeld() const noexcept
    {
        return hasHeld_;
    }

    TetrominoType HoldSystem::hold(TetrominoType current)
    {
        if (usedThisTurn_)
        {
            return current;
        }

        usedThisTurn_ = true;

        if (!hasHeld_)
        {
            hasHeld_ = true;
            heldType_ = current;
            return current; // new piece comes from queue (handled in Game)
        }

        TetrominoType swapped = heldType_;
        heldType_ = current;

        return swapped;
    }
}