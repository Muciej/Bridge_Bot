file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${UTILS_LIB_NAME}/*.hpp")

add_library(${UTILS_LIB_NAME} INTERFACE)

target_include_directories(${UTILS_LIB_NAME} INTERFACE ../include)
