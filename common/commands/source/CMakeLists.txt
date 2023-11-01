file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${COMMAND_LIB_NAME}/*.hpp")

# add_library(${COMMAND_LIB_NAME} ${HEADER_LIST})
add_library(${COMMAND_LIB_NAME} INTERFACE)

# target_include_directories(${COMMAND_LIB_NAME} PUBLIC ../include)
target_include_directories(${COMMAND_LIB_NAME} INTERFACE ../include)

# target_compile_features(${COMMAND_LIB_NAME} PUBLIC cxx_std_17)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
