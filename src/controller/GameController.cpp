// src/controller/GameController.cpp
#include "GameController.h"

GameController::GameController(sf::RenderWindow& window)
    : m_window(window)
{
    m_menuView       = std::make_unique<MenuView>(window);
    m_gameView       = std::make_unique<GameView>(window);
    m_gameOverView   = std::make_unique<GameOverView>(window);
    m_statsView      = std::make_unique<StatisticsView>(window);
}

void GameController::transitionTo(AppState next)
{
    m_state = next;
    if (next == AppState::Playing)
        m_game.start();
}

// ── Event dispatch ────────────────────────────────────────────────────────────

void GameController::handleEvent(const sf::Event& event)
{
    switch (m_state)
    {
        case AppState::Menu:       handleMenuEvent(event);     break;
        case AppState::Playing:
        case AppState::Paused:     handlePlayingEvent(event);  break;
        case AppState::GameOver:   handleGameOverEvent(event); break;
        case AppState::Statistics: handleStatsEvent(event);    break;
    }
}

void GameController::handleMenuEvent(const sf::Event& event)
{
    // 1. Обробка клавіатури (залишається як було)
    if (const auto* kp = event.getIf<sf::Event::KeyPressed>())
    {
        switch (kp->code)
        {
            case sf::Keyboard::Key::Enter:  transitionTo(AppState::Playing); break;
            case sf::Keyboard::Key::S:      transitionTo(AppState::Statistics); break;
            case sf::Keyboard::Key::Escape: m_window.close(); break;
            default: break;
        }
    }
    // 2. Нове: Обробка кліку мишкою
    else if (const auto* mbp = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mbp->button == sf::Mouse::Button::Left)
        {
            // Передаємо координати миші у View
            auto clickedOption = m_menuView->handleClick(mbp->position);

            if (clickedOption.has_value())
            {
                switch (clickedOption.value())
                {
                    case MenuOption::Play:       transitionTo(AppState::Playing); break;
                    case MenuOption::Statistics: transitionTo(AppState::Statistics); break;
                    case MenuOption::Quit:       m_window.close(); break;
                }
            }
        }
    }
}

void GameController::handlePlayingEvent(const sf::Event& event)
{
    if (const auto* kp = event.getIf<sf::Event::KeyPressed>())
    {
        switch (kp->code)
        {
            case sf::Keyboard::Key::Left:
                m_leftHeld     = true;
                m_dasTriggered = false;
                m_dasAccum     = 0.0f;
                m_arrAccum     = 0.0f;
                m_game.moveLeft();
                break;
            case sf::Keyboard::Key::Right:
                m_rightHeld    = true;
                m_dasTriggered = false;
                m_dasAccum     = 0.0f;
                m_arrAccum     = 0.0f;
                m_game.moveRight();
                break;
            case sf::Keyboard::Key::Down:    m_game.softDrop();    break;
            case sf::Keyboard::Key::Up:
            case sf::Keyboard::Key::X:       m_game.rotateCW();    break;
            case sf::Keyboard::Key::Z:       m_game.rotateCCW();   break;
            case sf::Keyboard::Key::Space:   m_game.hardDrop();    break;
            case sf::Keyboard::Key::C:
            case sf::Keyboard::Key::LShift:  m_game.holdPiece();   break;
            case sf::Keyboard::Key::P:
            case sf::Keyboard::Key::Escape:  m_game.togglePause(); break;
            default: break;
        }
    }
    else if (const auto* kr = event.getIf<sf::Event::KeyReleased>())
    {
        if (kr->code == sf::Keyboard::Key::Left)  m_leftHeld  = false;
        if (kr->code == sf::Keyboard::Key::Right) m_rightHeld = false;
    }
}

void GameController::handleGameOverEvent(const sf::Event& event)
{
    if (const auto* kp = event.getIf<sf::Event::KeyPressed>())
    {
        switch (kp->code)
        {
            case sf::Keyboard::Key::Enter:  transitionTo(AppState::Playing);    break;
            case sf::Keyboard::Key::S:      transitionTo(AppState::Statistics); break;
            case sf::Keyboard::Key::Escape: transitionTo(AppState::Menu);       break;
            default: break;
        }
    }
}

void GameController::handleStatsEvent(const sf::Event& event)
{
    if (const auto* kp = event.getIf<sf::Event::KeyPressed>())
    {
        if (kp->code == sf::Keyboard::Key::Escape ||
            kp->code == sf::Keyboard::Key::Enter)
        {
            transitionTo(AppState::Menu);
        }
    }
}

// ── Update ────────────────────────────────────────────────────────────────────

void GameController::update(float deltaTime)
{
    if (m_state == AppState::Playing)
    {
        updateAutoRepeat(deltaTime);
        m_game.update(deltaTime);

        if (m_game.isGameOver())
            m_state = AppState::GameOver;
    }
}

void GameController::updateAutoRepeat(float deltaTime)
{
    if (!m_leftHeld && !m_rightHeld) return;

    m_dasAccum += deltaTime;
    if (m_dasAccum >= k_dasDelay)
    {
        m_dasTriggered = true;
        m_arrAccum += deltaTime;
        if (m_arrAccum >= k_arrRate)
        {
            m_arrAccum -= k_arrRate;
            if (m_leftHeld)  m_game.moveLeft();
            if (m_rightHeld) m_game.moveRight();
        }
    }
}

// ── Render ────────────────────────────────────────────────────────────────────

void GameController::render()
{
    switch (m_state)
    {
        case AppState::Menu:
            m_menuView->render();
            break;
        case AppState::Playing:
        case AppState::Paused:
            m_gameView->render(m_game);
            break;
        case AppState::GameOver:
            m_gameView->render(m_game);
            m_gameOverView->render(m_game);
            break;
        case AppState::Statistics:
            m_statsView->render(m_game.getStats(),
                                m_game.getScore(),
                                m_game.getLevel());
            break;
    }
}