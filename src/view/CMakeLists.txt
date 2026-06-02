add_library(TetrisView STATIC
        GameView.cpp
        MenuView.cpp
        PauseView.cpp
        StatisticsView.cpp
        SettingsView.cpp
        GameOverView.cpp
        AnimationSystem.cpp
)

target_include_directories(TetrisView PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TetrisView
        PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
        TetrisModel
)