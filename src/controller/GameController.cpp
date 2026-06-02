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
        , input_()
        , stateMachine_()
    {
    }

    void GameController::handleEvent(const sf::Event& event)
    {
        input_.process(event, stateMachine_, game_);

        if (const auto* key = event.getIf<sf::Event::KeyPressed>())
        {
            switch (stateMachine_.current())
            {
                case State::Menu:
                    if (key->code == sf::Keyboard::Key::Up)   menuView_.moveUp();
                    if (key->code == sf::Keyboard::Key::Down) menuView_.moveDown();
                    if (key->code == sf::Keyboard::Key::Enter)
                    {
                        auto opt = menuView_.selectedOption();
                        if (opt == view::MenuOption::StartGame)  stateMachine_.setState(State::Playing);
                        if (opt == view::MenuOption::Settings)   stateMachine_.setState(State::Settings);
                        if (opt == view::MenuOption::Exit)       stateMachine_.requestExit();
                    }
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

                default:
                    break;
            }
        }
    }

    void GameController::update(float dt)
    {
        input_.update(dt, game_);

        if (stateMachine_.current() == State::Playing)
        {
            game_.update(dt);
            gameView_.update(dt);

            if (game_.state() == model::GameState::GameOver)
                stateMachine_.setState(State::GameOver);
        }

        if (stateMachine_.current() == State::Menu)
            menuView_.update(dt);
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

            default:
                window_.display();
                break;
        }
    }

    void GameController::updateGame(float dt)   { (void)dt; }
    void GameController::updateMenu(float dt)   { (void)dt; }
    void GameController::updatePause(float dt)  { (void)dt; }
    void GameController::updateGameOver(float dt){ (void)dt; }
}