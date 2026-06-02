add_library(TetrisController STATIC
        GameController.cpp
        InputController.cpp
        StateMachine.cpp
)

target_include_directories(TetrisController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TetrisController
        PUBLIC
        TetrisModel
        TetrisView
        TetrisState
)