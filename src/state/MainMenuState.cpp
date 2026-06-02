#include "MainMenuState.h"

namespace state
{
    MainMenuState::MainMenuState(sf::RenderWindow& window,
                                 controller::StateMachine& stateMachine)
        : window_(window)
        , stateMachine_(stateMachine)
        , menuView_(window)
    {
    }

    void MainMenuState::handleEvent(const sf::Event& event)
    {
        // Новий синтаксис SFML 3 для отримання події натискання клавіші
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            switch (keyPressed->code)
            {
                case sf::Keyboard::Key::Up:
                    menuView_.moveUp();
                    break;

                case sf::Keyboard::Key::Down:
                    menuView_.moveDown();
                    break;

                case sf::Keyboard::Key::Enter:
                {
                    // Виправляємо: викликаємо метод selectedOption()
                    auto option = menuView_.selectedOption();

                    switch (option)
                    {
                        case view::MenuOption::StartGame:
                            stateMachine_.setState(controller::State::Playing);
                            break;

                        case view::MenuOption::Statistics:
                            stateMachine_.setState(controller::State::Statistics);
                            break;

                        case view::MenuOption::Leaderboard:
                            stateMachine_.setState(controller::State::Leaderboard);
                            break;

                        case view::MenuOption::Settings:
                            stateMachine_.setState(controller::State::Settings);
                            break;

                        case view::MenuOption::Exit:
                            stateMachine_.requestExit();
                            break;
                    }
                    break;
                }

                default:
                    break;
            }
        }
    }

    void MainMenuState::update(float dt)
    {
        menuView_.update(dt);
    }

    void MainMenuState::render()
    {
        window_.clear(sf::Color(10, 10, 10));

        menuView_.render();

        window_.display();
    }
}