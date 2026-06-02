#include "SettingsState.h"

namespace state
{
    SettingsState::SettingsState(sf::RenderWindow& window,
                                 controller::StateMachine& stateMachine,
                                 model::SettingsManager& settings)
        : window_(window)
        , stateMachine_(stateMachine)
        , settings_(settings)
        , settingsView_(window)
    {
    }

    void SettingsState::handleEvent(const sf::Event& event)
    {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            switch (keyPressed->code)
            {
                case sf::Keyboard::Key::Escape:
                    stateMachine_.setState(controller::State::Menu);
                    break;

                case sf::Keyboard::Key::Up:
                    settingsView_.moveUp();
                    break;

                case sf::Keyboard::Key::Down:
                    settingsView_.moveDown();
                    break;

                case sf::Keyboard::Key::Left:
                    settingsView_.decreaseValue();
                    // Тут твій контролер згодом викличе реальні зміни конфігу, наприклад: settings_.set...
                    break;

                case sf::Keyboard::Key::Right:
                    settingsView_.increaseValue();
                    break;

                default:
                    break;
            }
        }
    }

    void SettingsState::update(float dt)
    {
        settingsView_.update(dt);
    }

    void SettingsState::render()
    {
        settingsView_.render();
    }
}