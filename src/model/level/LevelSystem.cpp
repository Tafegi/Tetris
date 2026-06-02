#include "LevelSystem.h"

namespace model
{
    LevelSystem::LevelSystem()
        : level_(0),
          totalLines_(0)
    {
    }

    void LevelSystem::reset()
    {
        level_ = 0;
        totalLines_ = 0;
    }

    void LevelSystem::addLines(int linesCleared)
    {
        if (linesCleared <= 0)
            return;

        totalLines_ += linesCleared;

        updateLevel();
    }

    void LevelSystem::updateLevel()
    {
        // Classic guideline: level increases every 10 lines
        level_ = totalLines_ / 10;
    }

    std::int32_t LevelSystem::level() const noexcept
    {
        return level_;
    }

    std::int32_t LevelSystem::totalLines() const noexcept
    {
        return totalLines_;
    }

    double LevelSystem::gravity() const noexcept
    {
        // simplified guideline gravity curve
        // higher level → faster drop

        const double base = 1.0;
        const double factor = 0.8;

        double speed = base;

        for (int i = 0; i < level_; ++i)
        {
            speed *= factor;
        }

        return speed < 0.05 ? 0.05 : speed;
    }
}