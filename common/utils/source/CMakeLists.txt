file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${UTILS_LIB_NAME}/*.hpp")

# if any .cpp file appers, add it here, between existing variables
# add_library(${UTILS_LIB_NAME} ${HEADER_LIST})
add_library(${UTILS_LIB_NAME} INTERFACE)

# target_include_directories(${UTILS_LIB_NAME} PUBLIC ../include)
target_include_directories(${UTILS_LIB_NAME} INTERFACE ../include)

# target_compile_features(${UTILS_LIB_NAME} PUBLIC cxx_std_17)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
