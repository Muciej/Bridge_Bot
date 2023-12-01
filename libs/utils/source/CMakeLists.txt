file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${UTILS_LIB_NAME}/*.hpp")

set(SOURCES
    Bid.cpp
    Bidding.cpp
    Card.cpp
    Dealer.cpp
    Exceptions.cpp
    Game.cpp
    MoveCorrectnessChecker.cpp
    Player.cpp
    Printer.cpp
    Trick.cpp
    CardsUtils.cpp
)

add_library(${UTILS_LIB_NAME} ${SOURCES} ${HEADER_LIST})

target_include_directories(${UTILS_LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${UTILS_LIB_NAME}
    compiler_flags
)
