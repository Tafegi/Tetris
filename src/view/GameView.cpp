#include "GameView.h"
#include "model/game/Game.h"
#include "model/board/Board.h"
#include "model/tetromino/Tetromino.h"
#include <string>

GameView::GameView(sf::RenderWindow& window)
    : m_window(window)
{
    // Graceful font fallback – ship a font in assets/ or use system font
    if (!m_font.openFromFile("assets/fonts/Roboto-Regular.ttf"))
        m_font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    m_cellShape.setSize({k_cellSize - 1.f, k_cellSize - 1.f});

    m_boardBorder.setSize({k_cellSize * Board::k_cols + 2.f,
                           k_cellSize * k_visibleRows + 2.f});
    m_boardBorder.setPosition({k_boardLeft - 1.f, k_boardTop - 1.f});
    m_boardBorder.setFillColor(sf::Color::Transparent);
    m_boardBorder.setOutlineColor(sf::Color(80, 80, 100));
    m_boardBorder.setOutlineThickness(1.f);
}

void GameView::render(const Game& game)
{
    drawBoard(game);
    drawGhostPiece(game);
    drawActivePiece(game);
    drawHUD(game);
    drawNextPanel(game);
    drawHoldPanel(game);
    m_window.draw(m_boardBorder);

    if (game.isPaused())
        drawPausedOverlay();
}

void GameView::drawCell(int col, int row, sf::Color color, float alpha)
{
    const float px = k_boardLeft + col * k_cellSize;
    const float py = k_boardTop  + (row - Board::k_hiddenRows) * k_cellSize;

    color.a = static_cast<uint8_t>(255.f * alpha);
    m_cellShape.setPosition({px, py});
    m_cellShape.setFillColor(color);
    // Subtle highlight on top-left edges
    m_cellShape.setOutlineColor(sf::Color(255, 255, 255, 30));
    m_cellShape.setOutlineThickness(-1.f);
    m_window.draw(m_cellShape);
}

void GameView::drawBoard(const Game& game)
{
    const auto& board = game.getBoard();
    // Grid lines
    for (int r = 0; r < k_visibleRows; ++r)
    {
        for (int c = 0; c < Board::k_cols; ++c)
        {
            const int boardRow = r + Board::k_hiddenRows;
            if (board.isOccupied(c, boardRow))
            {
                drawCell(c, boardRow, board.getColor(c, boardRow));
            }
            else
            {
                // dim grid dot
                sf::CircleShape dot(1.f);
                dot.setFillColor(sf::Color(40, 40, 55));
                dot.setPosition({k_boardLeft + c * k_cellSize + k_cellSize * 0.5f - 1.f,
                                k_boardTop  + r * k_cellSize + k_cellSize * 0.5f - 1.f});
                m_window.draw(dot);
            }
        }
    }
}

void GameView::drawActivePiece(const Game& game)
{
    for (const auto& cell : game.getActivePiece().getAbsoluteCells())
    {
        if (cell.y < Board::k_hiddenRows) continue;
        drawCell(cell.x, cell.y, game.getActivePiece().getColor());
    }
}

void GameView::drawGhostPiece(const Game& game)
{
    const Tetromino ghost = game.getGhostPiece();
    sf::Color ghostColor  = ghost.getColor();
    for (const auto& cell : ghost.getAbsoluteCells())
    {
        if (cell.y < Board::k_hiddenRows) continue;
        drawCell(cell.x, cell.y, ghostColor, 0.25f);
    }
}

void GameView::drawPiecePreview(const Tetromino& piece, float originX, float originY)
{
    for (const auto& cell : piece.getCells())
    {
        sf::RectangleShape s({k_cellSize - 1.f, k_cellSize - 1.f});
        s.setPosition({originX + cell.x * k_cellSize,
                      originY + cell.y * k_cellSize});
        s.setFillColor(piece.getColor());
        s.setOutlineColor(sf::Color(255, 255, 255, 30));
        s.setOutlineThickness(-1.f);
        m_window.draw(s);
    }
}

void GameView::drawNextPanel(const Game& game)
{
    const float panelX = k_boardLeft + Board::k_cols * k_cellSize + 20.f;
    float       panelY = k_boardTop;

    // Label
    sf::Text label(m_font, "NEXT", 14);
    label.setFillColor(sf::Color(180, 180, 200));
    label.setPosition({panelX, panelY});
    m_window.draw(label);
    panelY += 24.f;

    for (int i = 0; i < PieceQueue::k_previewCount; ++i)
    {
        const Tetromino& piece = game.getQueue().peek(i);
        drawPiecePreview(piece, panelX, panelY);
        panelY += k_cellSize * 3.f;
    }
}

void GameView::drawHoldPanel(const Game& game)
{
    const float panelX = k_boardLeft - 5 * k_cellSize - 10.f;
    float       panelY = k_boardTop;

    sf::Text label(m_font, "HOLD", 14);
    label.setFillColor(sf::Color(180, 180, 200));
    label.setPosition({panelX, panelY});
    m_window.draw(label);
    panelY += 24.f;

    const auto& hold = game.getHold();
    if (hold.hasHeld())
    {
        const float alpha = hold.isLocked() ? 0.4f : 1.0f;
        const Tetromino& held = hold.getHeld();

        for (const auto& cell : held.getCells())
        {
            sf::RectangleShape s({k_cellSize - 1.f, k_cellSize - 1.f});
            sf::Color c = held.getColor();
            c.a = static_cast<uint8_t>(255.f * alpha);
            s.setPosition({panelX + cell.x * k_cellSize,
                           panelY + cell.y * k_cellSize});
            s.setFillColor(c);
            s.setOutlineColor(sf::Color(255, 255, 255, 20));
            s.setOutlineThickness(-1.f);
            m_window.draw(s);
        }
    }
}

void GameView::drawHUD(const Game& game)
{
    const float hudX = k_boardLeft - 5 * k_cellSize - 10.f;
    float       hudY = k_boardTop + 4 * k_cellSize + 20.f;

    auto drawLine = [&](const std::string& label, const std::string& value)
    {
        sf::Text tLabel(m_font, label, 12);
        tLabel.setFillColor(sf::Color(140, 140, 160));
        tLabel.setPosition({hudX, hudY});
        m_window.draw(tLabel);
        hudY += 16.f;

        sf::Text tValue(m_font, value, 18);
        tValue.setFillColor(sf::Color(230, 230, 255));
        tValue.setPosition({hudX, hudY});
        m_window.draw(tValue);
        hudY += 28.f;
    };

    drawLine("SCORE",    std::to_string(game.getScore().getScore()));
    drawLine("BEST",     std::to_string(game.getScore().getHighScore()));
    drawLine("LEVEL",    std::to_string(game.getLevel().getLevel()));
    drawLine("LINES",    std::to_string(game.getLevel().getTotalLines()));

    // Controls hint (bottom of window)
    const float hintY = 640.f;
    const std::string hint =
        "[←→] Move  [↑/X] CW  [Z] CCW  [Space] Drop  [C] Hold  [P] Pause";
    sf::Text hintText(m_font, hint, 10);
    hintText.setFillColor(sf::Color(80, 80, 100));
    hintText.setPosition({10.f, hintY});
    m_window.draw(hintText);
}

void GameView::drawPausedOverlay()
{
    // Semi-transparent overlay
    sf::RectangleShape overlay({static_cast<float>(m_window.getSize().x),
                                static_cast<float>(m_window.getSize().y)});
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    m_window.draw(overlay);

    sf::Text text(m_font, "PAUSED", 48);
    text.setFillColor(sf::Color::White);
    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    text.setPosition({m_window.getSize().x / 2.f, m_window.getSize().y / 2.f});
    m_window.draw(text);

    sf::Text sub(m_font, "Press P or ESC to resume", 16);
    sub.setFillColor(sf::Color(180, 180, 200));
    const sf::FloatRect sb = sub.getLocalBounds();
    sub.setOrigin({sb.size.x / 2.f, sb.size.y / 2.f});
    sub.setPosition({m_window.getSize().x / 2.f, m_window.getSize().y / 2.f + 60.f});
    m_window.draw(sub);
}