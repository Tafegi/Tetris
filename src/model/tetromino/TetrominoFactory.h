#pragma once

#include "Tetromino.h"

namespace model
{
    class TetrominoFactory
    {
    public:
        // BUG FIX: was declared `static` here but defined without `static`
        // in the .cpp — that is a compile/link error. Removed static.
        Tetromino create(TetrominoType type);
    };
}