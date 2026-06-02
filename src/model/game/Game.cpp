#include "Game.h"

namespace model
{
    Game::Game()
        : factory_(),
          activePiece_(factory_.create(TetrominoType::I)),
          state_(GameState::Running)
    {
        // Spawn real first piece from queue
        TetrominoType first = queue_.next();
        activePiece_ = factory_.create(first);
        hold_.resetTurn();
        gravityAccumulator_ = 0.0;
        timer_.start();
    }

    void Game::reset()
    {
        board_.clear();
        queue_.reset();
        hold_.reset();
        scoreSystem_.reset();
        levelSystem_.reset();
        timer_.reset();
        gravityAccumulator_ = 0.0;
        state_ = GameState::Running;

        TetrominoType next = queue_.next();
        activePiece_ = factory_.create(next);
        hold_.resetTurn();
        timer_.start();
    }

    void Game::update(float dt)
    {
        if (state_ != GameState::Running)
            return;

        timer_.update();
        gravityAccumulator_ += static_cast<double>(dt);

        double interval = levelSystem_.gravity();

        while (gravityAccumulator_ >= interval)
        {
            gravityAccumulator_ -= interval;
            tick();
            if (state_ != GameState::Running)
                return;
        }
    }

    void Game::tick()
    {
        if (state_ != GameState::Running) return;

        if (rules_.canMove(activePiece_, board_, 0, 1))
        {
            activePiece_.move(0, 1);
            return;
        }

        lockPiece();
        clearLines();
        spawnNext();
    }

    void Game::moveLeft()
    {
        if (state_ != GameState::Running) return;
        if (rules_.canMove(activePiece_, board_, -1, 0))
            activePiece_.move(-1, 0);
    }

    void Game::moveRight()
    {
        if (state_ != GameState::Running) return;
        if (rules_.canMove(activePiece_, board_, 1, 0))
            activePiece_.move(1, 0);
    }

    void Game::moveDown()
    {
        if (state_ != GameState::Running) return;
        if (rules_.canMove(activePiece_, board_, 0, 1))
        {
            activePiece_.move(0, 1);
            gravityAccumulator_ = 0.0;
        }
    }

    void Game::hardDrop()
    {
        if (state_ != GameState::Running) return;
        while (rules_.canMove(activePiece_, board_, 0, 1))
            activePiece_.move(0, 1);
        lockPiece();
        clearLines();
        spawnNext();
    }

    void Game::rotateCW()
    {
        if (state_ != GameState::Running) return;
        if (rules_.canRotate(activePiece_, board_, Rotation::East))
            activePiece_.rotateClockwise();
    }

    void Game::rotateCCW()
    {
        if (state_ != GameState::Running) return;
        if (rules_.canRotate(activePiece_, board_, Rotation::West))
            activePiece_.rotateCounterClockwise();
    }

    void Game::hold()
    {
        if (state_ != GameState::Running) return;
        if (!hold_.canHold()) return;

        TetrominoType current = activePiece_.type();

        if (!hold_.hasHeld())
        {
            hold_.hold(current);
            TetrominoType next = queue_.next();
            activePiece_ = factory_.create(next);
            hold_.resetTurn();
            gravityAccumulator_ = 0.0;
        }
        else
        {
            TetrominoType swapped = hold_.hold(current);
            activePiece_ = factory_.create(swapped);
            gravityAccumulator_ = 0.0;
        }
    }

    void Game::spawnNext()
    {
        TetrominoType next = queue_.next();
        activePiece_ = factory_.create(next);
        hold_.resetTurn();
        gravityAccumulator_ = 0.0;

        // BUG FIX: Game Over check AFTER spawn - if new piece immediately
        // collides with locked blocks on the board, only THEN it's game over.
        if (isGameOver())
            state_ = GameState::GameOver;
    }

    void Game::lockPiece()
    {
        board_.lock(activePiece_);
    }

    void Game::clearLines()
    {
        int cleared = static_cast<int>(board_.clearLines().size());
        if (cleared <= 0) return;

        levelSystem_.addLines(cleared);
        ScoreEvent event = rules_.evaluateClearEvent(cleared, false, false, false);
        scoreSystem_.addEvent(event, cleared);
    }

    bool Game::isGameOver() const
    {
        return board_.isCollision(activePiece_);
    }

    GameState Game::state() const noexcept { return state_; }
    const Board& Game::board() const noexcept { return board_; }
    const Tetromino& Game::activePiece() const noexcept { return activePiece_; }
    std::int64_t Game::score() const noexcept { return scoreSystem_.score(); }
    std::int32_t Game::level() const noexcept { return levelSystem_.level(); }
    std::int32_t Game::lines() const noexcept { return levelSystem_.totalLines(); }
    const PieceQueue& Game::queue() const noexcept { return queue_; }
    TetrominoType Game::heldPiece() const noexcept { return hold_.heldType(); }
    bool Game::hasHeldPiece() const noexcept { return hold_.hasHeld(); }
}