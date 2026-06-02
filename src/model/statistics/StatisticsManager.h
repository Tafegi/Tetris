#pragma once

#include <cstdint>
#include <array>

#include "../types/TetrominoType.h"

namespace model
{
    class StatisticsManager
    {
    public:
        StatisticsManager();

        void reset();

        void onPiecePlaced(TetrominoType type);
        void onLinesCleared(int lines);
        void onTetris();
        void onTSpin();
        void onPerfectClear();

        void addPlayTime(std::int64_t seconds);

        std::int64_t totalGames() const noexcept;
        std::int64_t totalPlayTime() const noexcept;

        std::int64_t totalLines() const noexcept;
        std::int64_t highestScore() const noexcept;

        const std::array<std::int64_t, 7>& pieceDistribution() const noexcept;

    private:
        void updateHighestScore(int score);

    private:
        std::int64_t totalGames_;
        std::int64_t totalPlayTime_;
        std::int64_t totalLines_;
        std::int64_t highestScore_;

        std::array<std::int64_t, 7> pieceDistribution_;
    };
}