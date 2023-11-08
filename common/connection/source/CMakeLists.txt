file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${CONNECTION_LIB_NAME}/*.hpp")

set(SOURCES
    TcpClient.cpp
)

add_library(${CONNECTION_LIB_NAME} ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(${CONNECTION_LIB_NAME} PUBLIC ../include)
target_link_libraries(${CONNECTION_LIB_NAME} 
    compiler_flags
    sockpp
    commands
)
