#pragma once

#include <vector>
#include "../types/TetrominoType.h"
#include "../types/Position.h"
#include "../types/Rotation.h"

namespace model
{
    class Tetromino
    {
    public:
        using Matrix = std::vector<std::vector<int>>;

        explicit Tetromino(TetrominoType type);

        void move(int dx, int dy);
        void rotateClockwise();
        void rotateCounterClockwise();

        const Matrix& shape() const noexcept;
        Position position() const noexcept;
        TetrominoType type() const noexcept;
        Rotation rotation() const noexcept;

        void setPosition(Position pos);
        void updateShape();

        // Додамо константу SIZE, яку шукає твій клас Board (Board.cpp:64)
        static constexpr int SIZE = 4;

    private:
        TetrominoType type_;
        Position position_{0, 0};
        Rotation rotation_{Rotation::Clockwise}; // Початкове значення з твого енуму
        Matrix shape_{SIZE, std::vector<int>(SIZE, 0)};
    };
}