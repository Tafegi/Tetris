#include "Tetromino.h"
#include <algorithm>

namespace model
{
    Tetromino::Tetromino(TetrominoType type)
        : type_(type)
        , rotation_(Rotation::North)
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
        switch (rotation_)
        {
            case Rotation::North: rotation_ = Rotation::East;  break;
            case Rotation::East:  rotation_ = Rotation::South; break;
            case Rotation::South: rotation_ = Rotation::West;  break;
            case Rotation::West:  rotation_ = Rotation::North; break;
        }
        updateShape();
    }

    void Tetromino::rotateCounterClockwise()
    {
        switch (rotation_)
        {
            case Rotation::North: rotation_ = Rotation::West;  break;
            case Rotation::West:  rotation_ = Rotation::South; break;
            case Rotation::South: rotation_ = Rotation::East;  break;
            case Rotation::East:  rotation_ = Rotation::North; break;
        }
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
        // Скидаємо матрицю
        for (auto& row : shape_)
            std::fill(row.begin(), row.end(), 0);

        switch (type_)
        {
            case TetrominoType::I:
                switch (rotation_)
                {
                    case Rotation::North:
                    case Rotation::South:
                        shape_ = {{0,0,0,0},
                                  {1,1,1,1},
                                  {0,0,0,0},
                                  {0,0,0,0}};
                        break;
                    case Rotation::East:
                    case Rotation::West:
                        shape_ = {{0,0,1,0},
                                  {0,0,1,0},
                                  {0,0,1,0},
                                  {0,0,1,0}};
                        break;
                }
                break;

            case TetrominoType::O:
                // O не обертається
                shape_ = {{0,1,1,0},
                          {0,1,1,0},
                          {0,0,0,0},
                          {0,0,0,0}};
                break;

            case TetrominoType::T:
                switch (rotation_)
                {
                    case Rotation::North:
                        shape_ = {{0,1,0,0},
                                  {1,1,1,0},
                                  {0,0,0,0},
                                  {0,0,0,0}};
                        break;
                    case Rotation::East:
                        shape_ = {{0,1,0,0},
                                  {0,1,1,0},
                                  {0,1,0,0},
                                  {0,0,0,0}};
                        break;
                    case Rotation::South:
                        shape_ = {{0,0,0,0},
                                  {1,1,1,0},
                                  {0,1,0,0},
                                  {0,0,0,0}};
                        break;
                    case Rotation::West:
                        shape_ = {{0,1,0,0},
                                  {1,1,0,0},
                                  {0,1,0,0},
                                  {0,0,0,0}};
                        break;
                }
                break;

            case TetrominoType::S:
                switch (rotation_)
                {
                    case Rotation::North:
                    case Rotation::South:
                        shape_ = {{0,1,1,0},
                                  {1,1,0,0},
                                  {0,0,0,0},
                                  {0,0,0,0}};
                        break;
                    case Rotation::East:
                    case Rotation::West:
                        shape_ = {{0,1,0,0},
                                  {0,1,1,0},
                                  {0,0,1,0},
                                  {0,0,0,0}};
                        break;
                }
                break;

            case TetrominoType::Z:
                switch (rotation_)
                {
                    case Rotation::North:
                    case Rotation::South:
                        shape_ = {{1,1,0,0},
                                  {0,1,1,0},
                                  {0,0,0,0},
                                  {0,0,0,0}};
                        break;
                    case Rotation::East:
                    case Rotation::West:
                        shape_ = {{0,0,1,0},
                                  {0,1,1,0},
                                  {0,1,0,0},
                                  {0,0,0,0}};
                        break;
                }
                break;

            case TetrominoType::J:
                switch (rotation_)
                {
                    case Rotation::North:
                        shape_ = {{1,0,0,0},
                                  {1,1,1,0},
                                  {0,0,0,0},
                                  {0,0,0,0}};
                        break;
                    case Rotation::East:
                        shape_ = {{0,1,1,0},
                                  {0,1,0,0},
                                  {0,1,0,0},
                                  {0,0,0,0}};
                        break;
                    case Rotation::South:
                        shape_ = {{0,0,0,0},
                                  {1,1,1,0},
                                  {0,0,1,0},
                                  {0,0,0,0}};
                        break;
                    case Rotation::West:
                        shape_ = {{0,1,0,0},
                                  {0,1,0,0},
                                  {1,1,0,0},
                                  {0,0,0,0}};
                        break;
                }
                break;

            case TetrominoType::L:
                switch (rotation_)
                {
                    case Rotation::North:
                        shape_ = {{0,0,1,0},
                                  {1,1,1,0},
                                  {0,0,0,0},
                                  {0,0,0,0}};
                        break;
                    case Rotation::East:
                        shape_ = {{0,1,0,0},
                                  {0,1,0,0},
                                  {0,1,1,0},
                                  {0,0,0,0}};
                        break;
                    case Rotation::South:
                        shape_ = {{0,0,0,0},
                                  {1,1,1,0},
                                  {1,0,0,0},
                                  {0,0,0,0}};
                        break;
                    case Rotation::West:
                        shape_ = {{1,1,0,0},
                                  {0,1,0,0},
                                  {0,1,0,0},
                                  {0,0,0,0}};
                        break;
                }
                break;
        }
    }
}