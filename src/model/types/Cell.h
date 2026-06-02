#pragma once

#include "TetrominoType.h"

namespace model
{
    struct Cell
    {
        bool occupied{false};
        TetrominoType type{TetrominoType::I};

        constexpr bool operator==(const Cell&) const noexcept = default;
    };
}