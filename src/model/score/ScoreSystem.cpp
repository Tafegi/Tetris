// src/model/score/ScoreSystem.cpp
#include "ScoreSystem.h"
#include <algorithm>

namespace {
    constexpr uint64_t k_basePoints[5] = {0, 100, 300, 500, 800};
}

void ScoreSystem::addClearPoints(int linesCleared, int level) noexcept
{
    const int clamped = std::clamp(linesCleared, 0, 4);
    m_score += k_basePoints[clamped] * static_cast<uint64_t>(level);
    m_highScore = std::max(m_score, m_highScore);
}

void ScoreSystem::addSoftDrop(int cells) noexcept
{
    m_score += static_cast<uint64_t>(cells);
    m_highScore = std::max(m_score, m_highScore);
}

void ScoreSystem::addHardDrop(int cells) noexcept
{
    m_score += static_cast<uint64_t>(cells) * 2;
    m_highScore = std::max(m_score, m_highScore);
}

void ScoreSystem::reset() noexcept
{
    m_score = 0;
    // High-score intentionally NOT reset so it persists across games.
}