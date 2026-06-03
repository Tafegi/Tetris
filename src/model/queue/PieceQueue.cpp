#include "PieceQueue.h"
#include <algorithm>
#include <random>
#include <chrono>

PieceQueue::PieceQueue()
    : m_rng(static_cast<uint32_t>(
          std::chrono::steady_clock::now().time_since_epoch().count()))
{
    reset();
}

void PieceQueue::reset()
{
    m_queue.clear();
    // Seed with enough pieces for preview + 1 active
    while (static_cast<int>(m_queue.size()) < k_previewCount + 1)
        refill();
}

void PieceQueue::refill()
{
    // Build a canonical 7-bag
    m_bag = { TetrominoType::I, TetrominoType::J, TetrominoType::L,
              TetrominoType::O, TetrominoType::S, TetrominoType::T,
              TetrominoType::Z };
    std::shuffle(m_bag.begin(), m_bag.end(), m_rng);

    for (auto t : m_bag)
        m_queue.push_back(TetrominoFactory::create(t));
}

Tetromino PieceQueue::pop()
{
    Tetromino front = std::move(m_queue.front());
    m_queue.pop_front();
    // Keep the queue topped up
    if (static_cast<int>(m_queue.size()) < k_previewCount + 1)
        refill();
    return front;
}

const Tetromino& PieceQueue::peek(int index) const
{
    return m_queue.at(static_cast<std::size_t>(index));
}