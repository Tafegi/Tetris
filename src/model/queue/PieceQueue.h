#pragma once

#include <deque>
#include "../types/TetrominoType.h"
#include "../random/RandomBagGenerator.h"

namespace model
{
    class PieceQueue
    {
    public:
        PieceQueue();

        TetrominoType next();
        TetrominoType peek(std::size_t index) const;

        void refillIfNeeded();
        void reset();

        std::size_t size() const noexcept;

    private:
        void fillQueue();

        static constexpr std::size_t QUEUE_SIZE = 6;

        std::deque<TetrominoType> queue_;
        RandomBagGenerator generator_;
    };
}