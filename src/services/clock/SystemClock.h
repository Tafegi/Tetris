#pragma once

#include <chrono>
#include "interfaces/IClock.h"

namespace service
{
    class SystemClock final : public interfaces::IClock
    {
    public:
        SystemClock();

        // Додаємо метод для внутрішнього скидання (якщо треба оновлювати кадр)
        void update();

        // Сигнатури методів тепер суворо const, як вимагає interfaces::IClock
        float getDeltaTime() const override;
        float getTime() const override;

    private:
        using Clock = std::chrono::steady_clock;

        Clock::time_point startTime_;
        mutable Clock::time_point lastTime_; // mutable, щоб фіксувати дельту всередині const
        mutable float deltaTime_{0.f};
    };
}