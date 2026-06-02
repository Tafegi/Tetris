#include "GameView.h"

namespace view
{
    GameView::GameView(sf::RenderWindow& window)
        : window_(window)
    {
        blockShape_.setSize({30.f, 30.f});
        ghostShape_.setSize({30.f, 30.f});

        ghostShape_.setFillColor(sf::Color(255, 255, 255, 60));
    }

    void GameView::render(const model::Game& game)
    {
        window_.clear(sf::Color::Black);

        drawBoard(game.board());
        drawGhost(game.activePiece(), game.board());
        drawPiece(game.activePiece());
        drawUI(game);

        animationSystem_.draw(window_);

        window_.display();
    }

    void GameView::update(float dt)
    {
        animationSystem_.update(dt);
    }

    void GameView::drawBoard(const model::Board& board)
    {
        const auto& grid = board.grid();

        for (std::size_t y = 0; y < grid.size(); ++y)
        {
            for (std::size_t x = 0; x < grid[y].size(); ++x)
            {
                // Перевіряємо прапорець .occupied нашої структури Cell
                if (!grid[y][x].occupied)
                    continue;

                blockShape_.setPosition(toScreen(static_cast<int>(x), static_cast<int>(y)));
                blockShape_.setFillColor(sf::Color::Blue);

                window_.draw(blockShape_);
            }
        }
    }

    void GameView::drawPiece(const model::Tetromino& piece)
    {
        const auto& shape = piece.shape();
        const auto pos = piece.position();

        // Малюємо фігуру за її матрицею 4x4
        for (int y = 0; y < model::Tetromino::SIZE; ++y)
        {
            for (int x = 0; x < model::Tetromino::SIZE; ++x)
            {
                if (shape[y][x] == 0)
                    continue;

                blockShape_.setPosition(toScreen(pos.x + x, pos.y + y));
                blockShape_.setFillColor(sf::Color::Green);

                window_.draw(blockShape_);
            }
        }
    }

    void GameView::drawGhost(const model::Tetromino& piece, const model::Board& board)
    {
        model::Tetromino ghost = piece;

        // Падаємо привидом вниз, поки не перетнемося з блоками/межами поля
        while (!board.isCollision(ghost))
        {
            ghost.move(0, 1);
        }
        ghost.move(0, -1); // Повертаємо на один крок назад у валидну позицію

        const auto& shape = ghost.shape();
        const auto pos = ghost.position();

        // Відображаємо привид фігури
        for (int y = 0; y < model::Tetromino::SIZE; ++y)
        {
            for (int x = 0; x < model::Tetromino::SIZE; ++x)
            {
                if (shape[y][x] == 0)
                    continue;

                ghostShape_.setPosition(toScreen(pos.x + x, pos.y + y));
                window_.draw(ghostShape_);
            }
        }
    }

    void GameView::drawUI(const model::Game& game)
    {
        (void)game; // Прибираємо зауваження про unused parameter для -Werror
    }

    sf::Vector2f GameView::toScreen(int x, int y) const
    {
        return sf::Vector2f(
            static_cast<float>(x * 30),
            static_cast<float>(y * 30)
        );
    }
}