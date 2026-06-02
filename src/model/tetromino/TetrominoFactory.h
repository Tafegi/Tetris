#pragma once

#include "Tetromino.h"

namespace model
{
    class TetrominoFactory
    {
    public:
        static Tetromino create(TetrominoType type);
    };
}