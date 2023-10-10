set(GameEngineName BridgeGameEngine)

add_executable(${GameEngineName})

target_include_directories(${GameEngineName}
    PRIVATE ./include
)

target_sources(${GameEngineName}
    PRIVATE ./source/main.cpp
)

add_subdirectory(ut)
