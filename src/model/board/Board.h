#pragma once

#include <vector>
#include "../types/Cell.h"
#include "../tetromino/Tetromino.h"

namespace model
{
    class Board
    {
    public:
        // Робимо константи великими літерами, як у твоему .cpp коді
        static constexpr int WIDTH = 10;
        static constexpr int HEIGHT = 20;

        // Оголошуємо аліас Grid, який використовується в .cpp
        using Grid = std::vector<std::vector<Cell>>;

        Board();

        void clear();

        // Поєднуємо валідацію: .cpp називає це isCollision, давай залишимо цю назву
        bool isCollision(const Tetromino& piece) const;

        void lock(const Tetromino& piece);

        // Повертаємо вектор індексів, як реалізовано в .cpp
        std::vector<int> clearLines();

        const Grid& grid() const noexcept;

    private:
        Grid grid_;

        bool isInside(int x, int y) const;
    };
}