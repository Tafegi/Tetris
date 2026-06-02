#pragma once

namespace interfaces
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual void clear() = 0;
        virtual void display() = 0;
    };
}