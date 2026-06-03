cmake_minimum_required(VERSION 3.20)
project(Tetris VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# ── Find SFML 3.x ─────────────────────────────────────────────────────────────
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

# ── Sources ───────────────────────────────────────────────────────────────────
set(SOURCES
        src/main.cpp

        src/core/Application.cpp
        src/core/Application.h

        src/controller/GameController.cpp
        src/controller/GameController.h

        src/model/board/Board.cpp
        src/model/board/Board.h
        src/model/game/Game.cpp
        src/model/game/Game.h
        src/model/hold/HoldSystem.cpp
        src/model/hold/HoldSystem.h
        src/model/level/LevelSystem.cpp
        src/model/level/LevelSystem.h
        src/model/queue/PieceQueue.cpp
        src/model/queue/PieceQueue.h
        src/model/score/ScoreSystem.cpp
        src/model/score/ScoreSystem.h
        src/model/statistics/StatisticsManager.cpp
        src/model/statistics/StatisticsManager.h
        src/model/tetromino/Tetromino.cpp
        src/model/tetromino/Tetromino.h
        src/model/tetromino/TetrominoFactory.cpp
        src/model/tetromino/TetrominoFactory.h
        src/model/timer/GameTimer.cpp
        src/model/timer/GameTimer.h

        src/view/GameOverView.cpp
        src/view/GameOverView.h
        src/view/GameView.cpp
        src/view/GameView.h
        src/view/MenuView.cpp
        src/view/MenuView.h
        src/view/StatisticsView.cpp
        src/view/StatisticsView.h
)

add_executable(Tetris ${SOURCES})

target_include_directories(Tetris PRIVATE src)

# SFML 3.x uses namespaced targets
target_link_libraries(Tetris PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)

# Copy assets next to the binary
add_custom_command(TARGET Tetris POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Tetris>/assets
        COMMENT "Copying assets..."
)