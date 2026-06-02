#pragma once

#include <vector>
#include <random>

#include "../types/TetrominoType.h"

namespace model
{
    class RandomBagGenerator
    {
    public:
        RandomBagGenerator();

        TetrominoType next();
        void reset();

    private:
        void refillBag();
        void shuffleBag();

    private:
        std::vector<TetrominoType> bag_;
        std::size_t index_;

        std::mt19937 rng_;
    };
}