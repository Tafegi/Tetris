#include "EnterNameState.h"

namespace state
{
    EnterNameState::EnterNameState(sf::RenderWindow& window,
                                   controller::StateMachine& stateMachine)
        : window_(window)
        , stateMachine_(stateMachine)
        , titleText_(font_) // Явна ініціалізація шрифту для SFML 3
        , inputText_(font_) // Явна ініціалізація шрифту для SFML 3
    {
        if (!font_.openFromFile("assets/fonts/Roboto-Regular.ttf")) {
            // обробка помилки за бажанням
        }

        titleText_.setCharacterSize(48);
        titleText_.setString("ENTER YOUR NAME");
        titleText_.setFillColor(sf::Color::Cyan);
        titleText_.setPosition({100.f, 80.f}); // Фігурні дужки для sf::Vector2f

        inputText_.setCharacterSize(32);
        inputText_.setFillColor(sf::Color::White);
        inputText_.setPosition({100.f, 160.f}); // Фігурні дужки для sf::Vector2f
    }

    void EnterNameState::handleEvent(const sf::Event& event)
    {
        // 1. Обробка введення тексту в SFML 3
        if (const auto* textEntered = event.getIf<sf::Event::TextEntered>())
        {
            processInput(textEntered->unicode);
        }

        // 2. Обробка натискання клавіш керування в SFML 3
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Enter && !playerName_.empty())
            {
                stateMachine_.setState(controller::State::Menu);
            }

            if (keyPressed->code == sf::Keyboard::Key::Backspace)
            {
                if (!playerName_.empty())
                {
                    playerName_.pop_back();
                    inputText_.setString(playerName_);
                }
            }
        }
    }

    void EnterNameState::update(float)
    {
    }

    void EnterNameState::render()
    {
        window_.clear(sf::Color(10, 10, 15));
        drawUI();
        window_.display();
    }

    void EnterNameState::processInput(char32_t unicode)
    {
        // Дозволяємо лише базові символи ASCII для нікнейму
        if (unicode >= 32 && unicode < 127 && playerName_.size() < 15)
        {
            playerName_ += static_cast<char>(unicode);
            inputText_.setString(playerName_);
        }
    }

    void EnterNameState::drawUI()
    {
        window_.draw(titleText_);
        window_.draw(inputText_);
    }
}