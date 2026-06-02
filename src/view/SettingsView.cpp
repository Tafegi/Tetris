#include "SettingsView.h"
#include <algorithm>
#include <cstdint>

namespace view
{
    SettingsView::SettingsView(sf::RenderWindow& window)
        : window_(window),
          title_(font_) // Явна ініціалізація шрифту для головного тексту
    {
        if (!font_.openFromFile("assets/fonts/Roboto-Regular.ttf")) {
            // обробка помилки за бажанням
        }

        title_.setCharacterSize(48);
        title_.setString("SETTINGS");
        title_.setFillColor(sf::Color::White);

        labels_ = {
            "Resolution",
            "Fullscreen",
            "Master Volume",
            "Music Volume",
            "SFX Volume",
            "DAS",
            "ARR",
            "Ghost Piece",
            "FPS Limit",
            "VSync",
            "Back"
        };

        for (const auto& l : labels_)
        {
            // В SFML 3 обов'язково передаємо шрифт у конструктор sf::Text
            sf::Text t(font_);
            t.setCharacterSize(22);
            t.setString(l + " : value");
            t.setFillColor(sf::Color::White);

            items_.push_back(t);
        }
    }

    void SettingsView::update(float dt)
    {
        animate(dt);
    }

    void SettingsView::animate(float dt)
    {
        anim_ += dt * 5.f;
        if (anim_ > 1.f)
            anim_ = 0.f;
    }

    void SettingsView::render()
    {
        drawBackground();
        drawTitle();
        drawItems();

        window_.display();
    }

    void SettingsView::drawBackground()
    {
        sf::RectangleShape bg;
        bg.setSize({
            static_cast<float>(window_.getSize().x),
            static_cast<float>(window_.getSize().y)
        });

        bg.setFillColor(sf::Color(18, 18, 18));
        window_.draw(bg);
    }

    void SettingsView::drawTitle()
    {
        title_.setPosition({100.f, 50.f}); // Загортаємо в {} для sf::Vector2f
        window_.draw(title_);
    }

    void SettingsView::drawItems()
    {
        float y = 140.f;

        for (std::size_t i = 0; i < items_.size(); ++i)
        {
            auto& text = items_[i];
            text.setPosition({120.f, y + i * 40.f}); // Загортаємо в {}

            if (static_cast<int>(i) == selectedIndex_)
            {
                sf::Color c = sf::Color::Cyan;
                // Заміна sf::Uint8 на стандартний std::uint8_t
                c.a = static_cast<std::uint8_t>(200 + 55 * anim_);
                text.setFillColor(c);
            }
            else
            {
                text.setFillColor(sf::Color::White);
            }

            window_.draw(text);
        }
    }

    void SettingsView::moveUp()
    {
        selectedIndex_ = std::max(0, selectedIndex_ - 1);
    }

    void SettingsView::moveDown()
    {
        selectedIndex_ = std::min(
            static_cast<int>(items_.size()) - 1,
            selectedIndex_ + 1
        );
    }

    int SettingsView::selectedIndex() const noexcept
    {
        return selectedIndex_;
    }

    void SettingsView::increaseValue()
    {
        // intentionally UI-only stub
    }

    void SettingsView::decreaseValue()
    {
        // intentionally UI-only stub
    }
}