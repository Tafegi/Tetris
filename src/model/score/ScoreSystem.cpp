#include "ScoreSystem.h"

namespace model
{
    ScoreSystem::ScoreSystem()
        : score_(0),
          combo_(0),
          backToBack_(false),
          lastWasTetrisOrTSpin_(false)
    {
    }

    void ScoreSystem::reset()
    {
        score_ = 0;
        combo_ = 0;
        backToBack_ = false;
        lastWasTetrisOrTSpin_ = false;
    }

    void ScoreSystem::addEvent(ScoreEvent event, int linesCleared)
    {
        updateCombo(linesCleared);
        updateBackToBack(event, linesCleared);

        score_ += calculateScore(event, linesCleared);
    }

    void ScoreSystem::updateCombo(int linesCleared)
    {
        if (linesCleared > 0)
        {
            ++combo_;
        }
        else
        {
            combo_ = 0;
        }
    }

    void ScoreSystem::updateBackToBack(ScoreEvent event, int )
    {
        bool isPowerClear =
            event == ScoreEvent::Tetris ||
            event == ScoreEvent::TSpinSingle ||
            event == ScoreEvent::TSpinDouble ||
            event == ScoreEvent::TSpinTriple ||
            event == ScoreEvent::PerfectClear;

        if (isPowerClear)
        {
            if (lastWasTetrisOrTSpin_)
            {
                backToBack_ = true;
            }
            lastWasTetrisOrTSpin_ = true;
        }
        else
        {
            lastWasTetrisOrTSpin_ = false;
        }
    }

    std::int64_t ScoreSystem::calculateScore(ScoreEvent event, int linesCleared) const
    {
        int base = 0;

        switch (event)
        {
            case ScoreEvent::Single:       base = 100; break;
            case ScoreEvent::Double:       base = 300; break;
            case ScoreEvent::Triple:       base = 500; break;
            case ScoreEvent::Tetris:       base = 800; break;

            case ScoreEvent::TSpinMini:    base = 100; break;
            case ScoreEvent::TSpinSingle:  base = 200; break;
            case ScoreEvent::TSpinDouble:  base = 600; break;
            case ScoreEvent::TSpinTriple:  base = 900; break;

            case ScoreEvent::SoftDrop:     base = 1 * linesCleared; break;
            case ScoreEvent::HardDrop:     base = 2 * linesCleared; break;

            case ScoreEvent::PerfectClear: base = 2000; break;
        }

        // combo multiplier
        if (combo_ > 1)
        {
            base += combo_ * 50;
        }

        // back-to-back bonus
        if (backToBack_ &&
            (event == ScoreEvent::Tetris ||
             event == ScoreEvent::TSpinSingle ||
             event == ScoreEvent::TSpinDouble ||
             event == ScoreEvent::TSpinTriple ||
             event == ScoreEvent::PerfectClear))
        {
            base = static_cast<int>(base * 1.5);
        }

        return base;
    }

    std::int64_t ScoreSystem::score() const noexcept
    {
        return score_;
    }

    std::int32_t ScoreSystem::combo() const noexcept
    {
        return combo_;
    }

    bool ScoreSystem::backToBack() const noexcept
    {
        return backToBack_;
    }
}