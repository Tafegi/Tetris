#include "PieceQueue.h"

namespace model
{
    PieceQueue::PieceQueue()
    {
        fillQueue();
    }

    TetrominoType PieceQueue::next()
    {
        refillIfNeeded();

        TetrominoType front = queue_.front();
        queue_.pop_front();

        queue_.push_back(generator_.next());

        return front;
    }

    TetrominoType PieceQueue::peek(std::size_t index) const
    {
        if (index >= queue_.size())
        {
            return queue_.back();
        }

        return queue_[index];
    }

    void PieceQueue::refillIfNeeded()
    {
        while (queue_.size() < QUEUE_SIZE)
        {
            queue_.push_back(generator_.next());
        }
    }

    void PieceQueue::reset()
    {
        queue_.clear();
        generator_.reset();
        fillQueue();
    }

    std::size_t PieceQueue::size() const noexcept
    {
        return queue_.size();
    }

    void PieceQueue::fillQueue()
    {
        while (queue_.size() < QUEUE_SIZE)
        {
            queue_.push_back(generator_.next());
        }
    }
}