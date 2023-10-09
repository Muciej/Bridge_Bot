set(BrdigeBotName BridgeBot)

add_executable(${BrdigeBotName})

target_include_directories(${BrdigeBotName}
    PRIVATE ./include
)

target_sources(${BrdigeBotName}
    PRIVATE ./source/main.cpp
)
