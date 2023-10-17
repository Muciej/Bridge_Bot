set(COMMAND_LIB_NAME commands)

add_library(${COMMAND_LIB_NAME} INTERFACE)

target_sources(${COMMAND_LIB_NAME} PUBLIC
    MultiThreadCommandContainer.hpp
    QueueContainer.hpp
)
