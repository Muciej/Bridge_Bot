find_package(Threads REQUIRED)

add_executable(TcpClientTest main.cpp)

target_link_libraries(TcpClientTest    
    Threads::Threads
    commands
    connection
)
