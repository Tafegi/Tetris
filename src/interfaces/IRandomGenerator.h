#pragma once

#include <cstdint>

namespace interfaces
{
    class IRandomGenerator
    {
    public:
        virtual ~IRandomGenerator() = default;

        virtual int next(int min, int max) = 0;
        virtual void seed(std::uint32_t value) = 0;
    };
}