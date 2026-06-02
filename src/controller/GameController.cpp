#include "GameController.h"

namespace controller
{
    GameController::GameController(sf::RenderWindow& window)
        : window_(window)
        , game_()
        , gameView_(window)
        , menuView_(window)
        , pauseView_(window)
        , gameOverView_(window)
        , statisticsView_(window)
        , settingsView_(window)
        , stateMachine_()
    {
        highScoreManager_.load("scores.dat");
    }

    GameController::~GameController()
    {
        highScoreManager_.save("scores.dat");
    }

    void GameController::handleEvent(const sf::Event& event)
    {
        // ----- Mouse moved: hover highlight in menus -----
        if (const auto* mm = event.getIf<sf::Event::MouseMoved>())
        {
            if (stateMachine_.current() == State::Menu)
                menuView_.handleMouseMove({mm->position.x, mm->position.y});
        }

        // ----- Mouse clicked -----
        if (const auto* mb = event.getIf<sf::Event::MouseButtonPressed>())
        {
            if (mb->button == sf::Mouse::Button::Left)
            {
                sf::Vector2i mp(mb->position.x, mb->position.y);

                if (stateMachine_.current() == State::Menu)
                {
                    if (menuView_.handleMouseClick(mp))
                        executeMenuOption(menuView_.selectedOption());
                }
                else if (stateMachine_.current() == State::GameOver)
                {
                    bool playAgain = false, mainMenu = false;
                    gameOverView_.handleMouseClick(mp, playAgain, mainMenu);
                    if (playAgain) { game_.reset(); stateMachine_.setState(State::Playing); }
                    if (mainMenu)  { stateMachine_.setState(State::Menu); }
                }
            }
        }

        // ----- Keyboard -----
        if (const auto* key = event.getIf<sf::Event::KeyPressed>())
        {
            switch (stateMachine_.current())
            {
                case State::Menu:
                    if (key->code == sf::Keyboard::Key::Up)    menuView_.moveUp();
                    if (key->code == sf::Keyboard::Key::Down)  menuView_.moveDown();
                    if (key->code == sf::Keyboard::Key::Enter) executeMenuOption(menuView_.selectedOption());
                    break;

                case State::Playing:
                    if (key->code == sf::Keyboard::Key::Escape) stateMachine_.setState(State::Pause);
                    if (key->code == sf::Keyboard::Key::Left)   game_.moveLeft();
                    if (key->code == sf::Keyboard::Key::Right)  game_.moveRight();
                    if (key->code == sf::Keyboard::Key::Down)   game_.moveDown();
                    if (key->code == sf::Keyboard::Key::Up)     game_.rotateCW();
                    if (key->code == sf::Keyboard::Key::Space)  game_.hardDrop();
                    if (key->code == sf::Keyboard::Key::C)      game_.hold();
                    break;

                case State::Pause:
                    if (key->code == sf::Keyboard::Key::Escape) stateMachine_.resume();
                    if (key->code == sf::Keyboard::Key::M)      stateMachine_.setState(State::Menu);
                    break;

                case State::GameOver:
                    if (key->code == sf::Keyboard::Key::Enter)
                    {
                        saveScore();
                        game_.reset();
                        stateMachine_.setState(State::Playing);
                    }
                    if (key->code == sf::Keyboard::Key::Escape)
                    {
                        saveScore();
                        stateMachine_.setState(State::Menu);
                    }
                    break;

                case State::Settings:
                    if (key->code == sf::Keyboard::Key::Up)     settingsView_.moveUp();
                    if (key->code == sf::Keyboard::Key::Down)   settingsView_.moveDown();
                    if (key->code == sf::Keyboard::Key::Left)   settingsView_.decreaseValue();
                    if (key->code == sf::Keyboard::Key::Right)  settingsView_.increaseValue();
                    if (key->code == sf::Keyboard::Key::Escape) stateMachine_.setState(State::Menu);
                    break;

                case State::Statistics:
                    if (key->code == sf::Keyboard::Key::Escape) stateMachine_.setState(State::Menu);
                    break;

                default: break;
            }
        }
    }

    void GameController::executeMenuOption(view::MenuOption opt)
    {
        switch (opt)
        {
            case view::MenuOption::StartGame:
                game_.reset();
                stateMachine_.setState(State::Playing);
                break;
            case view::MenuOption::Statistics:
                stateMachine_.setState(State::Statistics);
                break;
            case view::MenuOption::Leaderboard:
                stateMachine_.setState(State::Leaderboard);
                break;
            case view::MenuOption::Settings:
                stateMachine_.setState(State::Settings);
                break;
            case view::MenuOption::Exit:
                stateMachine_.requestExit();
                break;
        }
    }

    void GameController::saveScore()
    {
        if (game_.score() == 0) return;

        model::HighScoreEntry entry;
        entry.playerName  = "Player";
        entry.score       = game_.score();
        entry.level       = game_.level();
        entry.lines       = game_.lines();
        entry.durationSec = 0;
        entry.date        = "2025";

        highScoreManager_.add(entry);
        highScoreManager_.save("scores.dat");
    }

    void GameController::update(float dt)
    {
        if (stateMachine_.current() == State::Playing)
        {
            game_.update(dt);
            gameView_.update(dt);

            if (game_.state() == model::GameState::GameOver)
                stateMachine_.setState(State::GameOver);
        }

        if (stateMachine_.current() == State::Menu)
            menuView_.update(dt);

        if (stateMachine_.current() == State::Settings)
            settingsView_.update(dt);
    }

    void GameController::render()
    {
        window_.clear(sf::Color::Black);

        switch (stateMachine_.current())
        {
            case State::Menu:
                menuView_.render();
                break;
            case State::Playing:
                gameView_.render(game_);
                break;
            case State::Pause:
                gameView_.render(game_);
                pauseView_.render();
                break;
            case State::GameOver:
                gameOverView_.render(game_, "");
                break;
            case State::Settings:
                settingsView_.render();
                break;
            case State::Statistics:
                statisticsView_.render(statisticsManager_);
                break;
            default:
                window_.display();
                break;
        }
    }

    void GameController::updateGame(float dt)    { (void)dt; }
    void GameController::updateMenu(float dt)    { (void)dt; }
    void GameController::updatePause(float dt)   { (void)dt; }
    void GameController::updateGameOver(float dt){ (void)dt; }
}