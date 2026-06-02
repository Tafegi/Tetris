#include "ExitState.h"

namespace state
{
    ExitState::ExitState(sf::RenderWindow& window,
                         controller::StateMachine& stateMachine)
        : window_(window)
        , stateMachine_(stateMachine)
    {
        stateMachine_.requestExit();
    }

    void ExitState::handleEvent(const sf::Event&)
    {
        // no input allowed
    }

    void ExitState::update(float)
    {
        // nothing to update
    }

    void ExitState::render()
    {
        // optionally clear screen before close
        window_.clear(sf::Color::Black);
        window_.display();
    }
}