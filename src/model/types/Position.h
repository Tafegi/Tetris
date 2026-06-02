#pragma once

namespace model
{
    struct Position
    {
        int x{};
        int y{};

        constexpr bool operator==(const Position&) const noexcept = default;
    };
}