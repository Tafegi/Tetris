#include "MenuView.h"
#include <algorithm>
#include <cstdint>

namespace view
{
    MenuView::MenuView(sf::RenderWindow& window)
        : window_(window),
          titleText_(font_)
    {
        font_.openFromFile("assets/fonts/Roboto-Regular.ttf");

        titleText_.setCharacterSize(64);
        titleText_.setString("TETRIS");
        titleText_.setFillColor(sf::Color::White);

        labels_ = { "Start Game", "Statistics", "Leaderboard", "Settings", "Exit" };

        for (const auto& label : labels_)
        {
            sf::Text text(font_);
            text.setCharacterSize(30);
            text.setString(label);
            text.setFillColor(sf::Color::White);
            items_.push_back(text);
        }
    }

    void MenuView::update(float dt)
    {
        animateSelection(dt);
    }

    void MenuView::animateSelection(float dt)
    {
        selectorAnim_ += dt * 4.f;
        if (selectorAnim_ > 6.2832f) selectorAnim_ = 0.f;
    }

    void MenuView::render()
    {
        drawBackground();
        drawTitle();
        drawItems();
        window_.display();
    }

    void MenuView::drawBackground()
    {
        sf::RectangleShape bg;
        bg.setSize({(float)window_.getSize().x, (float)window_.getSize().y});
        bg.setFillColor(sf::Color(12, 12, 20));
        window_.draw(bg);
    }

    void MenuView::drawTitle()
    {
        // Center title
        auto bounds = titleText_.getLocalBounds();
        titleText_.setOrigin({bounds.size.x / 2.f, 0.f});
        titleText_.setPosition({window_.getSize().x / 2.f, 80.f});
        window_.draw(titleText_);
    }

    sf::FloatRect MenuView::itemRect(int i) const
    {
        // approximate hit rect for mouse detection
        return sf::FloatRect(
            {ITEM_X - 10.f, ITEM_START_Y + i * ITEM_STEP - 5.f},
            {320.f, 48.f}
        );
    }

    void MenuView::drawItems()
    {
        for (std::size_t i = 0; i < items_.size(); ++i)
        {
            auto& text = items_[i];
            text.setPosition({ITEM_X, ITEM_START_Y + i * ITEM_STEP});

            bool selected = (static_cast<int>(i) == selectedIndex_);

            if (selected)
            {
                // Draw highlight box
                sf::RectangleShape box({300.f, 44.f});
                box.setPosition({ITEM_X - 8.f, ITEM_START_Y + i * ITEM_STEP - 4.f});
                box.setFillColor(sf::Color(40, 40, 80, 180));
                box.setOutlineThickness(1.f);
                box.setOutlineColor(sf::Color(100, 100, 200));
                window_.draw(box);

                // Arrow indicator
                sf::Text arrow(font_);
                arrow.setCharacterSize(30);
                arrow.setString(">");
                float pulse = 0.5f + 0.5f * std::sin(selectorAnim_);
                arrow.setFillColor(sf::Color(
                    static_cast<std::uint8_t>(180 + 75 * pulse),
                    static_cast<std::uint8_t>(180 + 75 * pulse),
                    255));
                arrow.setPosition({ITEM_X - 30.f, ITEM_START_Y + i * ITEM_STEP});
                window_.draw(arrow);

                text.setFillColor(sf::Color::Yellow);
            }
            else
            {
                text.setFillColor(sf::Color(200, 200, 200));
            }

            window_.draw(text);
        }
    }

    void MenuView::moveUp()
    {
        selectedIndex_ = std::max(0, selectedIndex_ - 1);
    }

    void MenuView::moveDown()
    {
        selectedIndex_ = std::min(static_cast<int>(items_.size()) - 1, selectedIndex_ + 1);
    }

    // BUG FIX: mouse support — highlights item under cursor
    bool MenuView::handleMouseMove(sf::Vector2i mousePos)
    {
        for (int i = 0; i < static_cast<int>(items_.size()); ++i)
        {
            if (itemRect(i).contains({(float)mousePos.x, (float)mousePos.y}))
            {
                selectedIndex_ = i;
                return true;
            }
        }
        return false;
    }

    // BUG FIX: mouse click selects item
    bool MenuView::handleMouseClick(sf::Vector2i mousePos)
    {
        for (int i = 0; i < static_cast<int>(items_.size()); ++i)
        {
            if (itemRect(i).contains({(float)mousePos.x, (float)mousePos.y}))
            {
                selectedIndex_ = i;
                return true;  // caller should then call selectedOption()
            }
        }
        return false;
    }

    MenuOption MenuView::selectedOption() const
    {
        switch (selectedIndex_)
        {
            case 0: return MenuOption::StartGame;
            case 1: return MenuOption::Statistics;
            case 2: return MenuOption::Leaderboard;
            case 3: return MenuOption::Settings;
            default: return MenuOption::Exit;
        }
    }
}