#include "HoldSystem.h"
#include "model/tetromino/TetrominoFactory.h"

bool HoldSystem::hold(Tetromino& activePiece, Tetromino nextFromQueue)
{
    if (m_locked) return false;

    if (m_held.has_value())
    {
        // Swap held <-> active; reset position/rotation of both
        Tetromino newActive = TetrominoFactory::create(m_held->getType());
        m_held = TetrominoFactory::create(activePiece.getType());
        activePiece = std::move(newActive);
    }
    else
    {
        // First hold: store active, promote next from queue
        m_held      = TetrominoFactory::create(activePiece.getType());
        activePiece = std::move(nextFromQueue);
    }

    m_locked = true;
    return true;
}

void HoldSystem::unlock() noexcept
{
    m_locked = false;
}

void HoldSystem::reset() noexcept
{
    m_held.reset();
    m_locked = false;
}

bool HoldSystem::hasHeld() const noexcept
{
    return m_held.has_value();
}

const Tetromino& HoldSystem::getHeld() const
{
    return m_held.value();
}