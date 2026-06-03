// src/model/level/LevelSystem.cpp
#include "LevelSystem.h"
#include <algorithm>
#include <cmath>

void LevelSystem::addLines(int lines) noexcept
{
    m_totalLines += lines;
    updateLevel();
}

void LevelSystem::reset() noexcept
{
    m_totalLines = 0;
    m_level      = 1;
}

void LevelSystem::updateLevel() noexcept
{
    m_level = std::min(m_totalLines / 10 + 1, k_maxLevel);
}

float LevelSystem::getDropInterval() const noexcept
{
    // Guideline: frames = (0.8 - (level-1)*0.007)^(level-1) at 60fps
    const double frames = std::pow(0.8 - (m_level - 1) * 0.007, m_level - 1);
    return static_cast<float>(frames); // already in seconds at 60fps base
}