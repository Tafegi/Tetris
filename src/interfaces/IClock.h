#pragma once

namespace interfaces
{
    class IClock
    {
    public:
        virtual ~IClock() = default;

        virtual float getDeltaTime() const = 0;
        virtual float getTime() const = 0;
    };
}