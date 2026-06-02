#include "StatisticsManager.h"

namespace model
{
    StatisticsManager::StatisticsManager()
    {
        reset();
    }

    void StatisticsManager::reset()
    {
        totalGames_ = 0;
        totalPlayTime_ = 0;
        totalLines_ = 0;
        highestScore_ = 0;

        pieceDistribution_.fill(0);
    }

    void StatisticsManager::onPiecePlaced(TetrominoType type)
    {
        auto index = static_cast<std::size_t>(type);
        if (index < pieceDistribution_.size())
        {
            ++pieceDistribution_[index];
        }
    }

    void StatisticsManager::onLinesCleared(int lines)
    {
        if (lines > 0)
        {
            totalLines_ += lines;
        }
    }

    void StatisticsManager::onTetris()
    {
        // marker event (can be extended later)
    }

    void StatisticsManager::onTSpin()
    {
        // marker event (can be extended later)
    }

    void StatisticsManager::onPerfectClear()
    {
        // marker event (can be extended later)
    }

    void StatisticsManager::addPlayTime(std::int64_t seconds)
    {
        totalPlayTime_ += seconds;
    }

    std::int64_t StatisticsManager::totalGames() const noexcept
    {
        return totalGames_;
    }

    std::int64_t StatisticsManager::totalPlayTime() const noexcept
    {
        return totalPlayTime_;
    }

    std::int64_t StatisticsManager::totalLines() const noexcept
    {
        return totalLines_;
    }

    std::int64_t StatisticsManager::highestScore() const noexcept
    {
        return highestScore_;
    }

    const std::array<std::int64_t, 7>& StatisticsManager::pieceDistribution() const noexcept
    {
        return pieceDistribution_;
    }

    void StatisticsManager::updateHighestScore(int score)
    {
        if (score > highestScore_)
        {
            highestScore_ = score;
        }
    }
}