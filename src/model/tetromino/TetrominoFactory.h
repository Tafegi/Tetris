#pragma once

#include "Tetromino.h"
#include <memory>

/**
 * @brief Creates Tetromino instances from canonical SRS rotation tables.
 *
 * All rotation data is compiled into this translation unit so the rest
 * of the codebase only calls TetrominoFactory::create(type).
 */
class TetrominoFactory
{
public:
    TetrominoFactory()  = default;
    ~TetrominoFactory() = default;

    [[nodiscard]] static Tetromino create(TetrominoType type);

    // SRS wall-kick data for JLSTZ pieces (spawn→CW, CW→spawn, CW→180, ...)
    // Returns the 5 kick offsets for a given (fromRotation → toRotation) transition.
    [[nodiscard]] static std::vector<Vec2i> getWallKicks(TetrominoType type,
                                                          int fromRot,
                                                          int toRot);
private:
    static sf::Color colorFor(TetrominoType type) noexcept;
};