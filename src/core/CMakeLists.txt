add_library(TetrisCore STATIC Application.cpp Logger.cpp)
target_include_directories(TetrisCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(TetrisCore PRIVATE ${CMAKE_SOURCE_DIR}/src)

# ТІЛЬКИ ЦЯ СТРОЧКА:
target_link_libraries(TetrisCore PRIVATE SFML::Graphics SFML::Window SFML::System)

target_compile_features(TetrisCore PUBLIC cxx_std_20)