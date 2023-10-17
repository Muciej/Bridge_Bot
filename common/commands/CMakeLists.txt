set(COMMAND_LIB_NAME commands)

add_library(${COMMAND_LIB_NAME} INTERFACE)

target_sources(${COMMAND_LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/MultiThreadCommandContainer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QueueContainer.hpp
)

target_include_directories(${COMMAND_LIB_NAME}
    INTERFACE ${CMAKE_SOURCE_DIR}/common
)

add_subdirectory(ut)
