#include "GameTimer.h"

namespace model
{
    GameTimer::GameTimer()
        : deltaTime_(0.0),
          totalTime_(0.0),
          running_(false)
    {
        lastTick_ = Clock::now();
        startTime_ = lastTick_;
    }

    void GameTimer::reset()
    {
        deltaTime_ = 0.0;
        totalTime_ = 0.0;

        lastTick_ = Clock::now();
        startTime_ = lastTick_;

        running_ = false;
    }

    void GameTimer::start()
    {
        running_ = true;
        lastTick_ = Clock::now();
        startTime_ = lastTick_;
    }

    void GameTimer::stop()
    {
        running_ = false;
    }

    void GameTimer::update()
    {
        if (!running_)
            return;

        auto now = Clock::now();

        deltaTime_ = std::chrono::duration<double>(now - lastTick_).count();
        totalTime_ = std::chrono::duration<double>(now - startTime_).count();

        lastTick_ = now;
    }

    double GameTimer::deltaTime() const noexcept
    {
        return deltaTime_;
    }

    double GameTimer::totalTime() const noexcept
    {
        return totalTime_;
    }

    bool GameTimer::isRunning() const noexcept
    {
        return running_;
    }
}