add_library(TetrisServices STATIC
        persistence/JsonRepository.cpp
        clock/SystemClock.cpp
        resource/ResourceCache.cpp
)

target_include_directories(TetrisServices PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TetrisServices PUBLIC TetrisInterfaces)