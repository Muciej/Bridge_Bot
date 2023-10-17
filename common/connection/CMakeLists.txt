
set(CONNECTION_LIB_NAME connection)
find_package(Threads REQUIRED)

add_library(${CONNECTION_LIB_NAME} INTERFACE)

target_link_libraries(${CONNECTION_LIB_NAME}
    INTERFACE sockpp
)

target_include_directories(${CONNECTION_LIB_NAME}
    INTERFACE ${CMAKE_SOURCE_DIR}/common
)

target_sources(${CONNECTION_LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/SocketClient.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TcpClient.hpp
)
