#include "RandomBagGenerator.h"

#include <algorithm>
#include <chrono>

namespace model
{
    RandomBagGenerator::RandomBagGenerator()
        : index_(0)
    {
        rng_.seed(static_cast<std::uint32_t>(
            std::chrono::steady_clock::now().time_since_epoch().count()
        ));

        refillBag();
    }

    TetrominoType RandomBagGenerator::next()
    {
        if (index_ >= bag_.size())
        {
            refillBag();
        }

        return bag_[index_++];
    }

    void RandomBagGenerator::reset()
    {
        index_ = 0;
        refillBag();
    }

    void RandomBagGenerator::refillBag()
    {
        bag_ = {
            TetrominoType::I,
            TetrominoType::O,
            TetrominoType::T,
            TetrominoType::S,
            TetrominoType::Z,
            TetrominoType::J,
            TetrominoType::L
        };

        shuffleBag();
        index_ = 0;
    }

    void RandomBagGenerator::shuffleBag()
    {
        std::shuffle(bag_.begin(), bag_.end(), rng_);
    }
}