#include "MenuView.h"
#include <algorithm>
#include <cstdint>

namespace view
{
    MenuView::MenuView(sf::RenderWindow& window)
        : window_(window),
          titleText_(font_) // Явна ініціалізація шрифту для головного тексту
    {
        if (!font_.openFromFile("assets/fonts/Roboto-Regular.ttf")) {
            // обробка помилки за бажанням
        }

        titleText_.setCharacterSize(56);
        titleText_.setString("TETRIS");
        titleText_.setFillColor(sf::Color::White);

        labels_ = {
            "Start Game",
            "Statistics",
            "Leaderboard",
            "Settings",
            "Exit"
        };

        for (const auto& label : labels_)
        {
            // В SFML 3 конструктор тексту обов'язково приймає шрифт
            sf::Text text(font_);
            text.setCharacterSize(28);
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
        selectorAnim_ += dt * 6.f;
        if (selectorAnim_ > 1.f)
            selectorAnim_ = 0.f;
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
        bg.setSize({
            static_cast<float>(window_.getSize().x),
            static_cast<float>(window_.getSize().y)
        });

        bg.setFillColor(sf::Color(10, 10, 10));
        window_.draw(bg);
    }

    void MenuView::drawTitle()
    {
        titleText_.setPosition({100.f, 80.f}); // Фігурні дужки для sf::Vector2f
        window_.draw(titleText_);
    }

    void MenuView::drawItems()
    {
        float startY = 200.f;

        for (std::size_t i = 0; i < items_.size(); ++i)
        {
            auto& text = items_[i];

            text.setPosition({120.f, startY + i * 55.f}); // Загортаємо в {}

            if (static_cast<int>(i) == selectedIndex_)
            {
                // Ефект пульсації кольору підсвічування
                sf::Color pulse = sf::Color::Yellow;
                pulse.a = static_cast<std::uint8_t>(200 + 55 * selectorAnim_); // std::uint8_t замість sf::Uint8
                text.setFillColor(pulse);
            }
            else
            {
                text.setFillColor(sf::Color::White);
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
        selectedIndex_ = std::min(
            static_cast<int>(items_.size()) - 1,
            selectedIndex_ + 1
        );
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