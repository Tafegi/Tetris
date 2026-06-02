#include "Game.h"

namespace model
{
    Game::Game()
        : factory_(),
          activePiece_(factory_.create(TetrominoType::I)), // Явна ініціалізація фігури
          state_(GameState::Running)
    {
        spawnNext();
    }

    void Game::reset()
    {
        board_.clear();

        queue_.reset();
        hold_.reset();

        scoreSystem_.reset();
        levelSystem_.reset();

        timer_.reset();

        state_ = GameState::Running;

        spawnNext();
    }

    void Game::update(double /*dt*/)
    {
        if (state_ != GameState::Running)
            return;

        timer_.update();
    }

    void Game::tick()
    {
        if (state_ != GameState::Running)
            return;

        if (rules_.canMove(activePiece_, board_, 0, 1))
        {
            activePiece_.move(0, 1);
            return;
        }

        lockPiece();
        clearLines();

        if (isGameOver())
        {
            state_ = GameState::GameOver;
            return;
        }

        spawnNext();
    }

    void Game::moveLeft()
    {
        if (rules_.canMove(activePiece_, board_, -1, 0))
            activePiece_.move(-1, 0);
    }

    void Game::moveRight()
    {
        if (rules_.canMove(activePiece_, board_, 1, 0))
            activePiece_.move(1, 0);
    }

    void Game::moveDown()
    {
        if (rules_.canMove(activePiece_, board_, 0, 1))
            activePiece_.move(0, 1);
    }

    void Game::hardDrop()
    {
        while (rules_.canMove(activePiece_, board_, 0, 1))
        {
            activePiece_.move(0, 1);
        }

        lockPiece();
        clearLines();

        if (isGameOver())
        {
            state_ = GameState::GameOver;
            return;
        }

        spawnNext();
    }

    void Game::rotateCW()
    {
        if (rules_.canRotate(activePiece_, board_, Rotation::East))  // ← було Clockwise
        {
            activePiece_.rotateClockwise();
        }
    }

    void Game::rotateCCW()
    {
        if (rules_.canRotate(activePiece_, board_, Rotation::West))  // ← було CounterClockwise
        {
            activePiece_.rotateCounterClockwise();
        }
    }

    void Game::hold()
    {
        if (!hold_.canHold())
            return;

        TetrominoType current = activePiece_.type();
        TetrominoType swapped = hold_.hold(current);

        if (swapped == current && !hold_.hasHeld())
        {
            spawnNext();
        }
        else
        {
            activePiece_ = factory_.create(swapped);
        }
    }

    void Game::spawnNext()
    {
        TetrominoType next = queue_.next();
        activePiece_ = factory_.create(next);

        if (isGameOver())
        {
            state_ = GameState::GameOver;
        }
    }

    void Game::lockPiece()
    {
        board_.lock(activePiece_); // Виправлено: place -> lock
    }

    void Game::clearLines()
    {
        // Виправлено: отримуємо кількість елементів з вектора
        int cleared = static_cast<int>(board_.clearLines().size());

        if (cleared <= 0)
            return;

        levelSystem_.addLines(cleared);

        ScoreEvent event = rules_.evaluateClearEvent(
            cleared,
            false,
            false,
            false
        );

        scoreSystem_.addEvent(event, cleared);
    }

    bool Game::isGameOver() const
    {
        return board_.isCollision(activePiece_); // Виправлено: collides -> isCollision
    }

    GameState Game::state() const noexcept
    {
        return state_;
    }

    const Board& Game::board() const noexcept
    {
        return board_;
    }

    const Tetromino& Game::activePiece() const noexcept
    {
        return activePiece_;
    }

    std::int64_t Game::score() const noexcept
    {
        return scoreSystem_.score();
    }

    std::int32_t Game::level() const noexcept
    {
        return levelSystem_.level();
    }

    std::int32_t Game::lines() const noexcept
    {
        return levelSystem_.totalLines();
    }
}