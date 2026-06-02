#include "Board.h"
#include <algorithm>

namespace model
{
    Board::Board()
    {
        grid_.resize(HEIGHT, std::vector<Cell>(WIDTH));
        clear();
    }

    void Board::clear()
    {
        for (auto& row : grid_)
        {
            std::fill(row.begin(), row.end(), Cell{});
        }
    }

    const Board::Grid& Board::grid() const noexcept
    {
        return grid_;
    }

    bool Board::isInside(int x, int y) const
    {
        return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
    }

    bool Board::isCollision(const Tetromino& piece) const
    {
        const auto& shape = piece.shape();
        const auto pos = piece.position();

        for (int y = 0; y < Tetromino::SIZE; ++y)
        {
            for (int x = 0; x < Tetromino::SIZE; ++x)
            {
                if (shape[y][x] == 0)
                    continue;

                int bx = pos.x + x;
                int by = pos.y + y;

                if (bx < 0 || bx >= WIDTH || by >= HEIGHT)
                    return true;

                if (by < 0)
                    continue;

                // Якщо клітинка на полі вже зайнята
                if (grid_[by][bx].occupied)
                    return true;
            }
        }

        return false;
    }

    void Board::lock(const Tetromino& piece)
    {
        const auto& shape = piece.shape();
        const auto pos = piece.position();

        for (int y = 0; y < Tetromino::SIZE; ++y)
        {
            for (int x = 0; x < Tetromino::SIZE; ++x)
            {
                if (shape[y][x] == 0)
                    continue;

                int bx = pos.x + x;
                int by = pos.y + y;

                if (!isInside(bx, by))
                    continue;

                // Фіксуємо блок: виставляємо occupied = true та тип фігури
                grid_[by][bx].occupied = true;
                grid_[by][bx].type = piece.type();
            }
        }
    }

    std::vector<int> Board::clearLines()
    {
        std::vector<int> cleared;

        for (int y = 0; y < HEIGHT; ++y)
        {
            bool full = true;

            for (int x = 0; x < WIDTH; ++x)
            {
                // Якщо хоч одна клітинка в рядку порожня
                if (!grid_[y][x].occupied)
                {
                    full = false;
                    break;
                }
            }

            if (full)
            {
                cleared.push_back(y);
            }
        }

        // Видаляємо лінії знизу вгору
        for (int i = static_cast<int>(cleared.size()) - 1; i >= 0; --i)
        {
            int row = cleared[i];

            for (int y = row; y > 0; --y)
            {
                grid_[y] = grid_[y - 1];
            }

            std::fill(grid_[0].begin(), grid_[0].end(), Cell{});
        }

        return cleared;
    }
}