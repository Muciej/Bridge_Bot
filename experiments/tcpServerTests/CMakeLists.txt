find_package(Threads REQUIRED)

add_executable(TcpServerTest main.cpp)

target_link_libraries(TcpServerTest    
    Threads::Threads
    commands
    connection
)
