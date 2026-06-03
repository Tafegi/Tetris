#include "Game.h"
#include "model/tetromino/TetrominoFactory.h"
#include <algorithm>

namespace {
    constexpr float k_lockDelay        = 0.5f;  // seconds before piece locks
    constexpr int   k_spawnCol         = 3;     // left edge of spawn bounding-box
    constexpr int   k_spawnRow         = 0;     // top of board (hidden rows area)
}

Game::Game()
    : m_active(TetrominoFactory::create(TetrominoType::T))  // placeholder
    , m_gravityTimer(1.0f)
    , m_lockTimer(k_lockDelay)
{}

void Game::start()
{
    reset();
}

void Game::reset()
{
    m_board.reset();
    m_queue.reset();
    m_hold.reset();
    m_score.reset();
    m_level.reset();
    m_stats.reset();

    m_gameOver = false;
    m_paused   = false;
    m_started  = true;
    m_onGround = false;

    m_gravityTimer.setInterval(m_level.getDropInterval());
    m_gravityTimer.reset();
    m_lockTimer.setInterval(k_lockDelay);
    m_lockTimer.reset();

    spawnNext();
}

void Game::update(float deltaTime)
{
    if (!m_started || m_gameOver || m_paused) return;

    // Update gravity interval in case level changed
    m_gravityTimer.setInterval(m_level.getDropInterval());

    if (m_gravityTimer.update(deltaTime))
    {
        Tetromino dropped = m_active.moved(0, 1);
        if (m_board.canPlace(dropped))
        {
            m_active   = dropped;
            m_onGround = false;
            m_lockTimer.reset();
        }
        else
        {
            m_onGround = true;
        }
    }

    // Lock-delay: lock the piece after it sits on the ground
    if (m_onGround)
    {
        if (m_lockTimer.update(deltaTime))
            lockAndSpawn();
    }
}

// ── Player actions ────────────────────────────────────────────────────────────

void Game::moveLeft()
{
    if (m_gameOver || m_paused) return;
    tryMove(m_active.moved(-1, 0));
}

void Game::moveRight()
{
    if (m_gameOver || m_paused) return;
    tryMove(m_active.moved(1, 0));
}

void Game::softDrop()
{
    if (m_gameOver || m_paused) return;
    Tetromino down = m_active.moved(0, 1);
    if (m_board.canPlace(down))
    {
        m_active = down;
        m_score.addSoftDrop(1);
        m_onGround = false;
        m_lockTimer.reset();
    }
    else
    {
        m_onGround = true;
    }
}

void Game::hardDrop()
{
    if (m_gameOver || m_paused) return;
    const Tetromino ghost  = m_board.hardDropPosition(m_active);
    const int        cells = ghost.getPosition().y - m_active.getPosition().y;
    m_active = ghost;
    m_score.addHardDrop(cells);
    lockAndSpawn();
}

void Game::rotateCW()
{
    if (m_gameOver || m_paused) return;
    tryRotate(true);
}

void Game::rotateCCW()
{
    if (m_gameOver || m_paused) return;
    tryRotate(false);
}

void Game::holdPiece()
{
    if (m_gameOver || m_paused) return;
    // We need the "next from queue" only when the hold slot is empty
    if (!m_hold.hasHeld())
    {
        Tetromino next = m_queue.pop();
        m_hold.hold(m_active, std::move(next));
    }
    else
    {
        Tetromino dummy = TetrominoFactory::create(TetrominoType::T); // not used
        m_hold.hold(m_active, std::move(dummy));
    }
    // Reset position of the new active piece
    Vec2i spawnPos{k_spawnCol, k_spawnRow};
    m_active.setPosition(spawnPos);
    m_onGround = false;
    m_lockTimer.reset();
}

void Game::togglePause()
{
    m_paused = !m_paused;
}

// ── Accessors ─────────────────────────────────────────────────────────────────

Tetromino Game::getGhostPiece() const noexcept
{
    return m_board.hardDropPosition(m_active);
}

// ── Private helpers ───────────────────────────────────────────────────────────

bool Game::spawnNext()
{
    Tetromino next = m_queue.pop();
    next.setPosition({k_spawnCol, k_spawnRow});
    m_stats.recordPiece(next.getType());
    m_hold.unlock();

    if (!m_board.canPlace(next))
    {
        m_gameOver = true;
        return false;
    }
    m_active   = std::move(next);
    m_onGround = false;
    m_lockTimer.reset();
    m_gravityTimer.reset();
    return true;
}

bool Game::tryMove(const Tetromino& candidate)
{
    if (!m_board.canPlace(candidate)) return false;
    m_active = candidate;
    // If piece moved laterally while on ground, reset lock timer
    m_lockTimer.reset();
    return true;
}

bool Game::tryRotate(bool clockwise)
{
    Tetromino rotated = clockwise ? m_active.rotatedCW() : m_active.rotatedCCW();

    // Try base rotation first
    if (m_board.canPlace(rotated))
    {
        m_active = rotated;
        m_lockTimer.reset();
        return true;
    }

    // SRS wall-kick attempts
    const int fromRot = m_active.getRotation();
    const int toRot   = rotated.getRotation();
    const auto kicks  = TetrominoFactory::getWallKicks(m_active.getType(), fromRot, toRot);

    for (const auto& kick : kicks)
    {
        Tetromino kicked = rotated.moved(kick.x, -kick.y); // SRS y-axis: up is negative
        if (m_board.canPlace(kicked))
        {
            m_active = kicked;
            m_lockTimer.reset();
            return true;
        }
    }
    return false;
}

void Game::lockAndSpawn()
{
    m_board.lockPiece(m_active);
    const int lines = m_board.clearFullRows();

    if (lines > 0)
    {
        m_score.addClearPoints(lines, m_level.getLevel());
        m_level.addLines(lines);
        m_stats.recordLineClear(lines);
    }

    m_gravityTimer.setInterval(m_level.getDropInterval());
    spawnNext();
}