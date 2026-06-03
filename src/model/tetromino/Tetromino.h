// src/model/tetromino/Tetromino.h
#pragma once

#include <array>
#include <vector>
#include <SFML/Graphics/Color.hpp>

// ── Types ─────────────────────────────────────────────────────────────────────

enum class TetrominoType : uint8_t
{
    I = 0, J, L, O, S, T, Z,
    Count,
    None   // sentinel / empty cell
};

// A single cell offset from the pivot
struct Vec2i
{
    int x{0};
    int y{0};

    Vec2i operator+(const Vec2i& o) const noexcept { return {x + o.x, y + o.y}; }
    Vec2i operator-(const Vec2i& o) const noexcept { return {x - o.x, y - o.y}; }
    bool  operator==(const Vec2i& o) const noexcept { return x == o.x && y == o.y; }
};

// One rotation state: 4 cell offsets from the bounding-box origin
using RotationState = std::array<Vec2i, 4>;

// ── Tetromino ─────────────────────────────────────────────────────────────────

/**
 * @brief Pure-data representation of a Tetris piece (no rendering).
 *
 * Stores the piece type, current rotation index, and board position.
 * All four rotation states (0°, 90°, 180°, 270°) are pre-computed
 * from the canonical SRS tables baked into TetrominoFactory.
 */
class Tetromino
{
public:
    // rotations[0..3] = the four SRS states; color matches guideline
    Tetromino(TetrominoType          type,
              std::vector<RotationState> rotations,
              sf::Color              color);

    // ── Accessors ─────────────────────────────────────────────────────────
    [[nodiscard]] TetrominoType              getType()     const noexcept { return m_type; }
    [[nodiscard]] sf::Color                  getColor()    const noexcept { return m_color; }
    [[nodiscard]] const RotationState&       getCells()    const noexcept;
    [[nodiscard]] int                        getRotation() const noexcept { return m_rotation; }
    [[nodiscard]] Vec2i                      getPosition() const noexcept { return m_position; }

    // Absolute board positions of all four cells
    [[nodiscard]] std::array<Vec2i, 4>       getAbsoluteCells() const noexcept;

    // ── Mutators (return modified COPY – model stays functional) ───────────
    [[nodiscard]] Tetromino moved(int dx, int dy)      const noexcept;
    [[nodiscard]] Tetromino rotatedCW()                const noexcept;   // clockwise
    [[nodiscard]] Tetromino rotatedCCW()               const noexcept;   // counter-clockwise

    void setPosition(Vec2i pos) noexcept { m_position = pos; }

private:
    TetrominoType              m_type;
    std::vector<RotationState> m_rotations; // [0]=spawn, [1]=CW, [2]=180, [3]=CCW
    sf::Color                  m_color;
    Vec2i                      m_position{0, 0};
    int                        m_rotation{0}; // 0-3
};