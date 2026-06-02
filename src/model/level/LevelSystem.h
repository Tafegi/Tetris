#pragma once

#include <cstdint>

namespace model
{
    class LevelSystem
    {
    public:
        LevelSystem();

        void reset();

        void addLines(int linesCleared);

        std::int32_t level() const noexcept;
        std::int32_t totalLines() const noexcept;

        double gravity() const noexcept;

    private:
        void updateLevel();

    private:
        std::int32_t level_;
        std::int32_t totalLines_;
    };
}