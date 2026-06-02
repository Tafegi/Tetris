#include "GameView.h"
#include <sstream>

namespace view
{
    static sf::Color pieceColor(model::TetrominoType type)
    {
        switch (type)
        {
            case model::TetrominoType::I: return sf::Color(0, 240, 240);
            case model::TetrominoType::O: return sf::Color(240, 240, 0);
            case model::TetrominoType::T: return sf::Color(160, 0, 240);
            case model::TetrominoType::S: return sf::Color(0, 240, 0);
            case model::TetrominoType::Z: return sf::Color(240, 0, 0);
            case model::TetrominoType::J: return sf::Color(0, 0, 240);
            case model::TetrominoType::L: return sf::Color(240, 160, 0);
        }
        return sf::Color::White;
    }

    static constexpr float BLOCK   = 30.f;
    static constexpr float BOARD_X = 250.f;
    static constexpr float BOARD_Y = 20.f;

    GameView::GameView(sf::RenderWindow& window)
        : window_(window)
    {
        blockShape_.setSize({BLOCK - 1.f, BLOCK - 1.f});
        ghostShape_.setSize({BLOCK - 1.f, BLOCK - 1.f});
        ghostShape_.setOutlineThickness(1.f);

        font_.openFromFile("assets/fonts/Roboto-Regular.ttf");
    }

    void GameView::render(const model::Game& game)
    {
        // draw dark background
        sf::RectangleShape bg;
        bg.setSize({(float)window_.getSize().x, (float)window_.getSize().y});
        bg.setFillColor(sf::Color(15, 15, 25));
        window_.draw(bg);

        drawBoardBorder();
        drawBoard(game.board());
        drawGhost(game.activePiece(), game.board());
        drawPiece(game.activePiece());
        drawHUD(game);
        animationSystem_.draw(window_);
        window_.display();
    }

    void GameView::update(float dt)
    {
        animationSystem_.update(dt);
    }

    void GameView::drawBoardBorder()
    {
        float w = model::Board::WIDTH  * BLOCK;
        float h = model::Board::HEIGHT * BLOCK;

        // grid lines
        sf::RectangleShape line;
        line.setFillColor(sf::Color(35, 35, 55));
        for (int x = 0; x <= model::Board::WIDTH; ++x)
        {
            line.setSize({1.f, h});
            line.setPosition({BOARD_X + x * BLOCK, BOARD_Y});
            window_.draw(line);
        }
        for (int y = 0; y <= model::Board::HEIGHT; ++y)
        {
            line.setSize({w, 1.f});
            line.setPosition({BOARD_X, BOARD_Y + y * BLOCK});
            window_.draw(line);
        }

        // border
        sf::RectangleShape border({w + 4.f, h + 4.f});
        border.setPosition({BOARD_X - 2.f, BOARD_Y - 2.f});
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineThickness(2.f);
        border.setOutlineColor(sf::Color(80, 80, 140));
        window_.draw(border);
    }

    void GameView::drawBoard(const model::Board& board)
    {
        const auto& grid = board.grid();
        for (std::size_t y = 0; y < grid.size(); ++y)
            for (std::size_t x = 0; x < grid[y].size(); ++x)
            {
                if (!grid[y][x].occupied) continue;
                blockShape_.setFillColor(pieceColor(grid[y][x].type));
                blockShape_.setPosition(toScreen((int)x, (int)y));
                window_.draw(blockShape_);
            }
    }

    void GameView::drawPiece(const model::Tetromino& piece)
    {
        const auto& shape = piece.shape();
        const auto  pos   = piece.position();
        sf::Color   color = pieceColor(piece.type());
        for (int y = 0; y < model::Tetromino::SIZE; ++y)
            for (int x = 0; x < model::Tetromino::SIZE; ++x)
            {
                if (shape[y][x] == 0) continue;
                blockShape_.setFillColor(color);
                blockShape_.setPosition(toScreen(pos.x + x, pos.y + y));
                window_.draw(blockShape_);
            }
    }

    void GameView::drawGhost(const model::Tetromino& piece, const model::Board& board)
    {
        model::Tetromino ghost = piece;
        while (!board.isCollision(ghost)) ghost.move(0, 1);
        ghost.move(0, -1);

        sf::Color gc = pieceColor(piece.type());
        gc.a = 55;
        ghostShape_.setFillColor(gc);
        ghostShape_.setOutlineColor(sf::Color(gc.r, gc.g, gc.b, 140));

        const auto& shape = ghost.shape();
        const auto  pos   = ghost.position();
        for (int y = 0; y < model::Tetromino::SIZE; ++y)
            for (int x = 0; x < model::Tetromino::SIZE; ++x)
            {
                if (shape[y][x] == 0) continue;
                ghostShape_.setPosition(toScreen(pos.x + x, pos.y + y));
                window_.draw(ghostShape_);
            }
    }

    void GameView::drawHUD(const model::Game& game)
    {
        float panelX = BOARD_X + model::Board::WIDTH * BLOCK + 20.f;

        // --- Right panel: Score/Level/Lines ---
        sf::Text info(font_);
        info.setCharacterSize(20);
        info.setFillColor(sf::Color::White);

        std::ostringstream ss;
        ss << "SCORE\n" << game.score()
           << "\n\nLEVEL\n"  << game.level()
           << "\n\nLINES\n"  << game.lines();
        info.setString(ss.str());
        info.setPosition({panelX, BOARD_Y + 10.f});
        window_.draw(info);

        // --- Controls hint ---
        sf::Text hint(font_);
        hint.setCharacterSize(14);
        hint.setFillColor(sf::Color(120, 120, 150));
        hint.setString("Arrows - move\nUp     - rotate\nSpace  - hard drop\nDown   - soft drop\nC      - hold\nEsc    - pause");
        hint.setPosition({panelX, BOARD_Y + 310.f});
        window_.draw(hint);

        // --- NEXT queue ---
        sf::Text nextLbl(font_);
        nextLbl.setCharacterSize(16);
        nextLbl.setFillColor(sf::Color(180, 180, 220));
        nextLbl.setString("NEXT");
        nextLbl.setPosition({panelX, BOARD_Y + 200.f});
        window_.draw(nextLbl);

        for (std::size_t i = 0; i < 3 && i < game.queue().size(); ++i)
            drawMiniPiece(game.queue().peek(i), panelX, BOARD_Y + 225.f + i * 80.f);

        // --- HOLD ---
        sf::Text holdLbl(font_);
        holdLbl.setCharacterSize(16);
        holdLbl.setFillColor(sf::Color(180, 180, 220));
        holdLbl.setString("HOLD");
        holdLbl.setPosition({BOARD_X - 120.f, BOARD_Y + 10.f});
        window_.draw(holdLbl);

        if (game.hasHeldPiece())
            drawMiniPiece(game.heldPiece(), BOARD_X - 120.f, BOARD_Y + 38.f);
    }

    void GameView::drawMiniPiece(model::TetrominoType type, float px, float py)
    {
        model::Tetromino mini(type);
        const auto& shape = mini.shape();
        sf::Color color = pieceColor(type);

        sf::RectangleShape blk({20.f, 20.f});
        blk.setFillColor(color);

        for (int y = 0; y < model::Tetromino::SIZE; ++y)
            for (int x = 0; x < model::Tetromino::SIZE; ++x)
            {
                if (shape[y][x] == 0) continue;
                blk.setPosition({px + x * 21.f, py + y * 21.f});
                window_.draw(blk);
            }
    }

    sf::Vector2f GameView::toScreen(int x, int y) const
    {
        return {BOARD_X + x * BLOCK, BOARD_Y + y * BLOCK};
    }
}