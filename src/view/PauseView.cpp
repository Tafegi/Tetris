#include "PauseView.h"

namespace view
{
    PauseView::PauseView(sf::RenderWindow& window)
        : window_(window),
          titleText_(font_), // Явно передаємо шрифт для SFML 3
          hintText_(font_)   // Явно передаємо шрифт для SFML 3
    {
        if (!font_.openFromFile("assets/fonts/Roboto-Regular.ttf")) {
            // Тут за бажанням можна додати логування помилки
        }

        // Шрифти вже прив'язані, тепер налаштовуємо стилі
        titleText_.setCharacterSize(48);
        titleText_.setFillColor(sf::Color::White);
        titleText_.setString("PAUSED");

        hintText_.setCharacterSize(20);
        hintText_.setFillColor(sf::Color(200, 200, 200));
        hintText_.setString("Press ESC to resume");
    }

    void PauseView::render()
    {
        drawOverlay();
        drawTitle();
        drawHint();

        window_.display();
    }

    void PauseView::drawOverlay()
    {
        sf::RectangleShape overlay;
        overlay.setSize({
            static_cast<float>(window_.getSize().x),
            static_cast<float>(window_.getSize().y)
        });

        overlay.setFillColor(sf::Color(0, 0, 0, 180));
        window_.draw(overlay);
    }

    void PauseView::drawTitle()
    {
        titleText_.setPosition({100.f, 100.f});
        window_.draw(titleText_);
    }

    void PauseView::drawHint()
    {
        hintText_.setPosition({100.f, 200.f});
        window_.draw(hintText_);
    }
}