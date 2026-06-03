#pragma once

#include "model/tetromino/Tetromino.h"
#include "model/tetromino/TetrominoFactory.h"
#include <deque>
#include <array>
#include <random>

/**
 * @brief 7-bag randomiser with a visible "next" preview queue.
 *
 * The 7-bag system guarantees every piece type appears exactly once
 * before any type repeats.  We maintain a lookahead of k_previewCount
 * pieces so the view can draw the next-piece panel.
 */
class PieceQueue
{
public:
    static constexpr int k_previewCount = 5;

    PieceQueue();

    /// Pop the front piece (becomes the active piece).
    [[nodiscard]] Tetromino pop();

    /// Peek at the Nth upcoming piece (0 = next, k_previewCount-1 = furthest).
    [[nodiscard]] const Tetromino& peek(int index) const;

    void reset();

private:
    void refill();   // fill a new shuffled bag into the deque

    std::deque<Tetromino>          m_queue;
    std::array<TetrominoType, 7>   m_bag{};
    std::mt19937                   m_rng;
};