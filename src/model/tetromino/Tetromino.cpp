#include "Tetromino.h"
#include <algorithm>

namespace model
{
    Tetromino::Tetromino(TetrominoType type)
        : type_(type)
    {
        updateShape();
    }

    void Tetromino::move(int dx, int dy)
    {
        position_.x += dx;
        position_.y += dy;
    }

    void Tetromino::rotateClockwise()
    {
        rotation_ = Rotation::Clockwise;
        updateShape();
    }

    void Tetromino::rotateCounterClockwise()
    {
        rotation_ = Rotation::CounterClockwise;
        updateShape();
    }

    const Tetromino::Matrix& Tetromino::shape() const noexcept
    {
        return shape_;
    }

    Position Tetromino::position() const noexcept
    {
        return position_;
    }

    TetrominoType Tetromino::type() const noexcept
    {
        return type_;
    }

    Rotation Tetromino::rotation() const noexcept
    {
        return rotation_;
    }

    void Tetromino::setPosition(Position pos)
    {
        position_ = pos;
    }

    void Tetromino::updateShape()
    {
        for (auto& row : shape_) {
            std::fill(row.begin(), row.end(), 0);
        }

        if (type_ == TetrominoType::I)
        {
            shape_ = {
                {0,0,0,0},
                {1,1,1,1},
                {0,0,0,0},
                {0,0,0,0}
            };
        }
        else if (type_ == TetrominoType::O)
        {
            shape_ = {
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0},
                {0,0,0,0}
            };
        }
        else
        {
            shape_ = {
                {0,1,0,0},
                {1,1,1,0},
                {0,0,0,0},
                {0,0,0,0}
            };
        }
    }
}