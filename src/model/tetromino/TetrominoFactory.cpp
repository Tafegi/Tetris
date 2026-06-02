#include "TetrominoFactory.h"

namespace model
{
    Tetromino TetrominoFactory::create(TetrominoType type)
    {
        Tetromino piece(type);

        // spawn position (center top)
        piece.setPosition({3, 0});

        return piece;
    }
}