#pragma once

#include <optional>

// BUG FIX: removed `#include "../view/MenuView.h"` which created a
// circular dependency: view → model → controller/StateMachine → view.
// StateMachine does not actually need anything from MenuView.

namespace controller
{
    enum class State
    {
        Menu,
        Playing,
        Pause,
        GameOver,
        Statistics,
        Settings,
        EnterName,
        Leaderboard,
        Exit
    };

    class StateMachine
    {
    public:
        StateMachine();

        void setState(State state);

        State current() const noexcept;

        void requestExit();

        bool shouldExit() const noexcept;

        // Menu navigation
        void menuUp();
        void menuDown();
        void select();

        void resume();

        // optional: data bridge (lightweight)
        void setSelectedMenuIndex(int index);
        int selectedMenuIndex() const noexcept;

    private:
        State state_;

        bool exitRequested_{false};

        int menuIndex_{0};
    };
}