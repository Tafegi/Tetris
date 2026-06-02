#include "StatisticsState.h"

namespace state
{
    StatisticsState::StatisticsState(sf::RenderWindow& window,
                                     controller::StateMachine& stateMachine,
                                     const model::StatisticsManager& stats)
        : window_(window)
        , stateMachine_(stateMachine)
        , stats_(stats)
        , statisticsView_(window)
    {
    }

    void StatisticsState::handleEvent(const sf::Event& event)
    {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape)
            {
                stateMachine_.setState(controller::State::Menu);
            }
        }
    }

    void StatisticsState::update(float /*dt*/) {}

    void StatisticsState::render()
    {
        statisticsView_.render(stats_);
    }
}