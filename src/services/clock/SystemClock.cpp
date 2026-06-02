#include "SystemClock.h"

namespace service
{
    SystemClock::SystemClock()
        : startTime_(Clock::now())
        , lastTime_(Clock::now())
    {
    }

    void SystemClock::update()
    {
        auto now = Clock::now();
        std::chrono::duration<float> duration = now - lastTime_;
        deltaTime_ = duration.count();
        lastTime_ = now;
    }

    float SystemClock::getDeltaTime() const
    {
        auto now = Clock::now();
        std::chrono::duration<float> duration = now - lastTime_;
        lastTime_ = now; // Оновлюємо мітку для наступного виклику
        return duration.count();
    }

    float SystemClock::getTime() const
    {
        auto now = Clock::now();
        std::chrono::duration<float> duration = now - startTime_;
        return duration.count();
    }
}