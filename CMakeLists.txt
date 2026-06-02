cmake_minimum_required(VERSION 3.20)
project(TetrisEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#==================================================
# SFML (Чисте підключення)
#==================================================
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 3.1 COMPONENTS Graphics Window System REQUIRED)

include_directories("${CMAKE_SOURCE_DIR}/src")

#==================================================
# SUBDIRECTORIES & EXECUTABLE
#==================================================
add_subdirectory(src/core)
add_subdirectory(src/interfaces)
add_subdirectory(src/model)
add_subdirectory(src/services)
add_subdirectory(src/view)
add_subdirectory(src/controller)
add_subdirectory(src/state)

add_executable(Tetris src/main.cpp)

set(PROJECT_MODULES TetrisController TetrisView TetrisState TetrisCore TetrisModel TetrisServices)
target_link_libraries(Tetris PRIVATE ${PROJECT_MODULES})

# Лінкуємо тільки через SFML::Target (це автоматично підтягне всі шляхи)
foreach(MODULE ${PROJECT_MODULES})
    target_link_libraries(${MODULE} PUBLIC SFML::Graphics SFML::Window SFML::System)
endforeach()
target_link_libraries(Tetris PRIVATE SFML::Graphics SFML::Window SFML::System)

#==================================================
# DLL КОПІЮВАННЯ
#==================================================
if(WIN32)
    add_custom_command(TARGET Tetris POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "C:/SFML/bin/sfml-graphics-3.dll" "$<TARGET_FILE_DIR:Tetris>/"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "C:/SFML/bin/sfml-window-3.dll" "$<TARGET_FILE_DIR:Tetris>/"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "C:/SFML/bin/sfml-system-3.dll" "$<TARGET_FILE_DIR:Tetris>/"
    )
endif()