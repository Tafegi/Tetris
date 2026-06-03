#include "StatisticsManager.h"
#include <numeric>
#include <algorithm>

void StatisticsManager::recordPiece(TetrominoType type) noexcept
{
    const auto idx = static_cast<std::size_t>(type);
    if (idx < k_typeCount)
        ++m_pieceCounts[idx];
}

void StatisticsManager::recordLineClear(int lines) noexcept
{
    if (lines >= 1 && lines <= 4)
        ++m_lineClearCounts[lines - 1];
}

void StatisticsManager::reset() noexcept
{
    m_pieceCounts.fill(0);
    m_lineClearCounts.fill(0);
}

uint32_t StatisticsManager::getPieceCount(TetrominoType type) const noexcept
{
    const auto idx = static_cast<std::size_t>(type);
    return (idx < k_typeCount) ? m_pieceCounts[idx] : 0u;
}

uint32_t StatisticsManager::getTotalPieces() const noexcept
{
    return std::accumulate(m_pieceCounts.begin(), m_pieceCounts.end(), 0u);
}

uint32_t StatisticsManager::getLineClearCount(int lines) const noexcept
{
    if (lines >= 1 && lines <= 4)
        return m_lineClearCounts[lines - 1];
    return 0u;
}

uint32_t StatisticsManager::getTotalLinesCleared() const noexcept
{
    return std::accumulate(m_lineClearCounts.begin(), m_lineClearCounts.end(), 0u);
}