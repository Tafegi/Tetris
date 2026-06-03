// src/model/statistics/StatisticsManager.h
#pragma once
#include <array>
#include <cstdint>
#include "model/tetromino/Tetromino.h"

/**
 * @brief Accumulates per-game statistics (piece counts, line clear breakdown).
 */
class StatisticsManager
{
public:
    StatisticsManager() = default;

    void recordPiece(TetrominoType type) noexcept;
    void recordLineClear(int lines) noexcept; // lines = 1-4

    void reset() noexcept;

    [[nodiscard]] uint32_t getPieceCount(TetrominoType type)  const noexcept;
    [[nodiscard]] uint32_t getTotalPieces()                   const noexcept;
    [[nodiscard]] uint32_t getLineClearCount(int lines)       const noexcept; // 1-4
    [[nodiscard]] uint32_t getTotalLinesCleared()             const noexcept;

private:
    static constexpr std::size_t k_typeCount = 7;

    std::array<uint32_t, k_typeCount> m_pieceCounts{};
    std::array<uint32_t, 4>           m_lineClearCounts{}; // [0]=Singles … [3]=Tetrises
};