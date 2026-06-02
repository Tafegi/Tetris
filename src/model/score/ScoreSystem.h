#pragma once

#include <cstdint>

#include "../types/ScoreEvent.h"

namespace model
{
    class ScoreSystem
    {
    public:
        ScoreSystem();

        void reset();

        void addEvent(ScoreEvent event, int linesCleared = 0);

        std::int64_t score() const noexcept;
        std::int32_t combo() const noexcept;
        bool backToBack() const noexcept;

    private:
        void updateCombo(int linesCleared);
        void updateBackToBack(ScoreEvent event, int linesCleared);

        std::int64_t calculateScore(ScoreEvent event, int linesCleared) const;

    private:
        std::int64_t score_;

        std::int32_t combo_;
        bool backToBack_;

        bool lastWasTetrisOrTSpin_;
    };
}