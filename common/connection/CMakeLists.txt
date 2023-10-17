
set(CONNECTION_LIB_NAME connection)
find_package(Threads REQUIRED)

add_library(${CONNECTION_LIB_NAME} INTERFACE)

target_sources(${CONNECTION_LIB_NAME} PUBLIC
    SocketClient.hpp
)

target_link_libraries(${CONNECTION_LIB_NAME}
    INTERFACE commands
    sockpp
)
