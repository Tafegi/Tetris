#include "InputController.h"

namespace controller
{
    InputController::InputController() = default;

    void InputController::process(const sf::Event& event,
                                  StateMachine& stateMachine,
                                  model::Game& game)
    {
        handleMenuInput(event, stateMachine);
        handleGameInput(event, game);
    }

    void InputController::update(float dt, model::Game& game)
    {
        (void)game; // Заглушка для компілятора: параметр використовується

        if (leftHeld_)  { dasTimer_ += dt; }
        if (rightHeld_) { dasTimer_ += dt; }
    }

    void InputController::handleMenuInput(const sf::Event&, StateMachine&) {}
    void InputController::handleGameInput(const sf::Event&, model::Game&) {}
    void InputController::handlePauseInput(const sf::Event&, StateMachine&) {}
}