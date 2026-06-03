// src/model/tetromino/Tetromino.cpp
#include "Tetromino.h"

Tetromino::Tetromino(TetrominoType              type,
                     std::vector<RotationState> rotations,
                     sf::Color                  color)
    : m_type(type)
    , m_rotations(std::move(rotations))
    , m_color(color)
{}

const RotationState& Tetromino::getCells() const noexcept
{
    return m_rotations[static_cast<std::size_t>(m_rotation)];
}

std::array<Vec2i, 4> Tetromino::getAbsoluteCells() const noexcept
{
    std::array<Vec2i, 4> abs{};
    const auto& cells = getCells();
    for (int i = 0; i < 4; ++i)
        abs[i] = cells[i] + m_position;
    return abs;
}

Tetromino Tetromino::moved(int dx, int dy) const noexcept
{
    Tetromino copy = *this;
    copy.m_position.x += dx;
    copy.m_position.y += dy;
    return copy;
}

Tetromino Tetromino::rotatedCW() const noexcept
{
    Tetromino copy = *this;
    copy.m_rotation = (m_rotation + 1) % 4;
    return copy;
}

Tetromino Tetromino::rotatedCCW() const noexcept
{
    Tetromino copy = *this;
    copy.m_rotation = (m_rotation + 3) % 4; // +3 mod 4 == -1 mod 4
    return copy;
}