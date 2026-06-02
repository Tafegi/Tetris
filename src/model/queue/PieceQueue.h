#pragma once

#include <deque>
#include <vector>

#include "../types/TetrominoType.h"
#include "../random/RandomBagGenerator.h"

namespace model
{
    class PieceQueue
    {
    public:
        explicit PieceQueue();

        TetrominoType next();
        TetrominoType peek(std::size_t index) const;

        void refillIfNeeded();

        void reset();

        std::size_t size() const noexcept;

    private:
        void fillQueue();

    private:
        static constexpr std::size_t QUEUE_SIZE = 5;

        std::deque<TetrominoType> queue_;
        RandomBagGenerator generator_;
    };
}