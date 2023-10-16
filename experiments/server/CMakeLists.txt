find_package(Threads REQUIRED)

add_executable(Server server.cpp)

target_link_libraries(Server    
    Threads::Threads
    sockpp
)
