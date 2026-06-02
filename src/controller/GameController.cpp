#include "GameController.h"

namespace controller
{
    GameController::GameController(sf::RenderWindow& window)
        : window_(window)
        , game_()
        , gameView_(window)        // Виправлено: передаємо вікно
        , menuView_(window)        // Виправлено: передаємо вікно
        , pauseView_(window)       // Виправлено: передаємо вікно
        , gameOverView_(window)    // Виправлено: передаємо вікно
        , statisticsView_(window)  // Виправлено: передаємо вікно
        , settingsView_(window)    // Виправлено: передаємо вікно
        , input_()
        , stateMachine_()
    {
    }

    void GameController::handleEvent(const sf::Event& event)
    {
        input_.process(event, stateMachine_, game_);
    }

    void GameController::update(float dt)
    {
        input_.update(dt, game_);
        updateGame(dt);
    }

    void GameController::render()
    {
        window_.clear(sf::Color::Black);
        // Твоя логіка відображення активного стану
        window_.display();
    }

    void GameController::updateGame(float dt)
    {
        (void)dt; // Заглушка для компілятора: параметр використовується
    }

    void GameController::updateMenu(float dt)
    {
        (void)dt;
    }

    void GameController::updatePause(float dt)
    {
        (void)dt;
    }

    void GameController::updateGameOver(float dt)
    {
        (void)dt;
    }
}