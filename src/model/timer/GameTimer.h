#pragma once

#include <chrono>

namespace model
{
    // BUG FIX: GameTimer::start() was never called — timer was always
    // stopped (running_=false) so update() returned immediately and
    // gravity accumulator in Game never advanced.
    // Fixed by calling timer_.start() in Game constructor and reset().
    class GameTimer
    {
    public:
        using Clock = std::chrono::steady_clock;

    public:
        GameTimer();

        void reset();

        void start();
        void stop();

        void update();

        double deltaTime() const noexcept;
        double totalTime() const noexcept;

        bool isRunning() const noexcept;

    private:
        Clock::time_point lastTick_;
        Clock::time_point startTime_;

        double deltaTime_;
        double totalTime_;

        bool running_;
    };
}