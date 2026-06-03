// src/controller/GameController.h
#pragma once

#include "model/game/Game.h"
#include "view/GameView.h"
#include "view/GameOverView.h"
#include "view/MenuView.h"
#include "view/StatisticsView.h"

#include <SFML/Graphics.hpp>
#include <memory>

/**
 * @brief Manages application state and routes input/update/render calls.
 *
 * States: Menu → Playing → GameOver → Statistics → Menu (loop)
 */
class GameController
{
public:
    explicit GameController(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event);
    void update(float deltaTime);
    void render();

private:
    enum class AppState { Menu, Playing, Paused, GameOver, Statistics };

    void transitionTo(AppState next);

    // ── Input routing ──────────────────────────────────────────────────────
    void handleMenuEvent    (const sf::Event& event);
    void handlePlayingEvent (const sf::Event& event);
    void handleGameOverEvent(const sf::Event& event);
    void handleStatsEvent   (const sf::Event& event);

    // ── Auto-repeat for held movement keys ────────────────────────────────
    void updateAutoRepeat(float deltaTime);

    sf::RenderWindow& m_window;

    AppState          m_state{AppState::Menu};

    Game              m_game;

    // Views – constructed once, reused
    std::unique_ptr<MenuView>       m_menuView;
    std::unique_ptr<GameView>       m_gameView;
    std::unique_ptr<GameOverView>   m_gameOverView;
    std::unique_ptr<StatisticsView> m_statsView;

    // Auto-repeat (DAS / ARR)
    static constexpr float k_dasDelay = 0.170f; // Delayed Auto Shift
    static constexpr float k_arrRate  = 0.033f; // Auto Repeat Rate

    bool  m_leftHeld{false};
    bool  m_rightHeld{false};
    float m_dasAccum{0.0f};
    float m_arrAccum{0.0f};
    bool  m_dasTriggered{false};
};