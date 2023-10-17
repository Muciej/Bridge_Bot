find_package(Threads REQUIRED)

add_executable(Client client.cpp)

target_link_libraries(Client
    Threads::Threads
    sockpp
)
