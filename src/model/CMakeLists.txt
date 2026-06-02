add_library(TetrisModel STATIC
        board/Board.cpp
        tetromino/Tetromino.cpp
        tetromino/TetrominoFactory.cpp
        game/Game.cpp
        queue/PieceQueue.cpp
        hold/HoldSystem.cpp
        score/ScoreSystem.cpp
        level/LevelSystem.cpp
        statistics/StatisticsManager.cpp
        highscore/HighScoreManager.cpp
        settings/SettingsManager.cpp
        rules/GameplayRules.cpp
        random/RandomBagGenerator.cpp
        timer/GameTimer.cpp
)

# Додаємо шляхи до кореня моделі, папки типів та інших підпапок
target_include_directories(TetrisModel PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/types
        ${CMAKE_CURRENT_SOURCE_DIR}/board
        ${CMAKE_CURRENT_SOURCE_DIR}/tetromino
        ${CMAKE_CURRENT_SOURCE_DIR}/game
)

target_link_libraries(TetrisModel PUBLIC TetrisInterfaces)