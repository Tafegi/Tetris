// src/model/tetromino/TetrominoFactory.cpp
#include "TetrominoFactory.h"

// ── SRS rotation tables ───────────────────────────────────────────────────────
// Each piece has 4 rotation states; each state is 4 cell offsets (col, row)
// from the top-left of the spawn bounding box.

namespace
{

// Helper – build RotationState from 8 ints (x0,y0, x1,y1, x2,y2, x3,y3)
constexpr RotationState rs(int x0,int y0,int x1,int y1,
                            int x2,int y2,int x3,int y3)
{
    return {Vec2i{x0,y0}, Vec2i{x1,y1}, Vec2i{x2,y2}, Vec2i{x3,y3}};
}

// ── I piece ───────────────────────────────────────────────────────────────────
const std::vector<RotationState> k_I =
{
    rs(0,1, 1,1, 2,1, 3,1),   // 0  spawn  ████
    rs(2,0, 2,1, 2,2, 2,3),   // R  CW
    rs(0,2, 1,2, 2,2, 3,2),   // 2  180
    rs(1,0, 1,1, 1,2, 1,3),   // L  CCW
};

// ── J piece ───────────────────────────────────────────────────────────────────
const std::vector<RotationState> k_J =
{
    rs(0,0, 0,1, 1,1, 2,1),   // 0
    rs(1,0, 2,0, 1,1, 1,2),   // R
    rs(0,1, 1,1, 2,1, 2,2),   // 2
    rs(1,0, 1,1, 0,2, 1,2),   // L
};

// ── L piece ───────────────────────────────────────────────────────────────────
const std::vector<RotationState> k_L =
{
    rs(2,0, 0,1, 1,1, 2,1),   // 0
    rs(1,0, 1,1, 1,2, 2,2),   // R
    rs(0,1, 1,1, 2,1, 0,2),   // 2
    rs(0,0, 1,0, 1,1, 1,2),   // L
};

// ── O piece ───────────────────────────────────────────────────────────────────
const std::vector<RotationState> k_O =
{
    rs(1,0, 2,0, 1,1, 2,1),   // all rotations identical for O
    rs(1,0, 2,0, 1,1, 2,1),
    rs(1,0, 2,0, 1,1, 2,1),
    rs(1,0, 2,0, 1,1, 2,1),
};

// ── S piece ───────────────────────────────────────────────────────────────────
const std::vector<RotationState> k_S =
{
    rs(1,0, 2,0, 0,1, 1,1),   // 0
    rs(1,0, 1,1, 2,1, 2,2),   // R
    rs(1,1, 2,1, 0,2, 1,2),   // 2
    rs(0,0, 0,1, 1,1, 1,2),   // L
};

// ── T piece ───────────────────────────────────────────────────────────────────
const std::vector<RotationState> k_T =
{
    rs(1,0, 0,1, 1,1, 2,1),   // 0
    rs(1,0, 1,1, 2,1, 1,2),   // R
    rs(0,1, 1,1, 2,1, 1,2),   // 2
    rs(1,0, 0,1, 1,1, 1,2),   // L
};

// ── Z piece ───────────────────────────────────────────────────────────────────
const std::vector<RotationState> k_Z =
{
    rs(0,0, 1,0, 1,1, 2,1),   // 0
    rs(2,0, 1,1, 2,1, 1,2),   // R
    rs(0,1, 1,1, 1,2, 2,2),   // 2
    rs(1,0, 0,1, 1,1, 0,2),   // L
};

// ── SRS wall-kick tables ──────────────────────────────────────────────────────
// JLSTZ offsets: [from*4 + to] indexed by (fromRot*4 + toRot)
// Transitions: 0→R, R→0, R→2, 2→R, 2→L, L→2, L→0, 0→L
using KickList = std::vector<Vec2i>;

// clang-format off
const KickList k_kicksJLSTZ[8] =
{
    // 0→R
    {{0,0},{-1,0},{-1,1},{0,-2},{-1,-2}},
    // R→0
    {{0,0},{1,0},{1,-1},{0,2},{1,2}},
    // R→2
    {{0,0},{1,0},{1,-1},{0,2},{1,2}},
    // 2→R
    {{0,0},{-1,0},{-1,1},{0,-2},{-1,-2}},
    // 2→L
    {{0,0},{1,0},{1,1},{0,-2},{1,-2}},
    // L→2
    {{0,0},{-1,0},{-1,-1},{0,2},{-1,2}},
    // L→0
    {{0,0},{-1,0},{-1,-1},{0,2},{-1,2}},
    // 0→L
    {{0,0},{1,0},{1,1},{0,-2},{1,-2}},
};

const KickList k_kicksI[8] =
{
    // 0→R
    {{0,0},{-2,0},{1,0},{-2,-1},{1,2}},
    // R→0
    {{0,0},{2,0},{-1,0},{2,1},{-1,-2}},
    // R→2
    {{0,0},{-1,0},{2,0},{-1,2},{2,-1}},
    // 2→R
    {{0,0},{1,0},{-2,0},{1,-2},{-2,1}},
    // 2→L
    {{0,0},{2,0},{-1,0},{2,1},{-1,-2}},
    // L→2
    {{0,0},{-2,0},{1,0},{-2,-1},{1,2}},
    // L→0
    {{0,0},{1,0},{-2,0},{1,-2},{-2,1}},
    // 0→L
    {{0,0},{-1,0},{2,0},{-1,2},{2,-1}},
};
// clang-format on

// Map (fromRot, toRot) → index 0-7
int kickIndex(int from, int to)
{
    // Transitions in order matching the arrays above
    const std::pair<int,int> table[8] =
    { {0,1},{1,0},{1,2},{2,1},{2,3},{3,2},{3,0},{0,3} };
    for (int i = 0; i < 8; ++i)
        if (table[i].first == from && table[i].second == to)
            return i;
    return 0; // fallback
}

} // anonymous namespace

// ── Public API ────────────────────────────────────────────────────────────────

sf::Color TetrominoFactory::colorFor(TetrominoType type) noexcept
{
    switch (type)
    {
        case TetrominoType::I: return {0,   240, 240}; // cyan
        case TetrominoType::J: return {0,   0,   240}; // blue
        case TetrominoType::L: return {240, 160, 0  }; // orange
        case TetrominoType::O: return {240, 240, 0  }; // yellow
        case TetrominoType::S: return {0,   240, 0  }; // green
        case TetrominoType::T: return {160, 0,   240}; // purple
        case TetrominoType::Z: return {240, 0,   0  }; // red
        default:               return {128, 128, 128};
    }
}

Tetromino TetrominoFactory::create(TetrominoType type)
{
    const std::vector<RotationState>* rots = nullptr;
    switch (type)
    {
        case TetrominoType::I: rots = &k_I; break;
        case TetrominoType::J: rots = &k_J; break;
        case TetrominoType::L: rots = &k_L; break;
        case TetrominoType::O: rots = &k_O; break;
        case TetrominoType::S: rots = &k_S; break;
        case TetrominoType::T: rots = &k_T; break;
        case TetrominoType::Z: rots = &k_Z; break;
        default:               rots = &k_T; break;
    }
    return Tetromino{type, *rots, colorFor(type)};
}

std::vector<Vec2i> TetrominoFactory::getWallKicks(TetrominoType type,
                                                    int fromRot,
                                                    int toRot)
{
    const int idx = kickIndex(fromRot % 4, toRot % 4);
    if (type == TetrominoType::I)
        return k_kicksI[idx];
    if (type == TetrominoType::O)
        return {{0,0}}; // O never kicks
    return k_kicksJLSTZ[idx];
}