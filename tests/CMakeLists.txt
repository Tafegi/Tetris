add_executable(TetrisTests
        BoardTests.cpp
        TetrominoTests.cpp
        WallKickTests.cpp
        RandomBagTests.cpp
        ScoreSystemTests.cpp
        LevelSystemTests.cpp
        HoldSystemTests.cpp
        HighScoreTests.cpp
        StatisticsTests.cpp
        GameTests.cpp
        TestMain.cpp
)

target_link_libraries(TetrisTests
        PRIVATE
        TetrisModel
        TetrisCore
        gtest
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(TetrisTests)