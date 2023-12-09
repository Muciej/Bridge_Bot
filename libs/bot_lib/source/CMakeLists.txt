file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${BOT_LIB_NAME}/*.hpp")

set(SOURCES
    Bot.cpp
    moves_optimizations/MergeSuccessingCards.cpp
    state_evaluator/BaseEvaluator.cpp
    bid_evaluator/BidEvaluator.cpp
    bot_utils/MovesGenerator.cpp
)

add_library(${BOT_LIB_NAME} ${SOURCES} ${HEADER_LIST})

target_include_directories(${BOT_LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${BOT_LIB_NAME}
    compiler_flags
    utils
    connection
    commands
)
