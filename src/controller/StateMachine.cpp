#include "StateMachine.h"

namespace controller
{
    // Тот самий конструктор, який шукав лінкер.
    // Задаємо стартовий стан гри — Головне Меню.
    StateMachine::StateMachine()
        : state_(State::Menu)
        , exitRequested_(false)
        , menuIndex_(0)
    {
    }

    void StateMachine::setState(State state)
    {
        state_ = state;
    }

    State StateMachine::current() const noexcept
    {
        return state_;
    }

    void StateMachine::requestExit()
    {
        exitRequested_ = true;
    }

    bool StateMachine::shouldExit() const noexcept
    {
        return exitRequested_;
    }

    void StateMachine::menuUp()
    {
        if (menuIndex_ > 0)
        {
            menuIndex_--;
        }
    }

    void StateMachine::menuDown()
    {
        // Припустимо, у тебе в меню 3 пункти (Грати, Налаштування, Вихід)
        // Можеш підставити тут свою максимальну кількість пунктів мінус 1
        if (menuIndex_ < 2)
        {
            menuIndex_++;
        }
    }

    void StateMachine::select()
    {
        // Логіка переходу зі станів меню при натисканні Enter
        if (state_ == State::Menu)
        {
            if (menuIndex_ == 0) state_ = State::Playing;
            else if (menuIndex_ == 1) state_ = State::Settings;
            else if (menuIndex_ == 2) exitRequested_ = true;
        }
    }

    void StateMachine::resume()
    {
        if (state_ == State::Pause)
        {
            state_ = State::Playing;
        }
    }

    void StateMachine::setSelectedMenuIndex(int index)
    {
        menuIndex_ = index;
    }

    int StateMachine::selectedMenuIndex() const noexcept
    {
        return menuIndex_;
    }
}