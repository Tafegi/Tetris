add_library(TetrisState STATIC
        MainMenuState.cpp
        PlayingState.cpp
        PauseState.cpp
        StatisticsState.cpp
        LeaderboardState.cpp
        SettingsState.cpp
        EnterNameState.cpp
        GameOverState.cpp
        ExitState.cpp
)

target_include_directories(TetrisState PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TetrisState
        PUBLIC
        TetrisController
)