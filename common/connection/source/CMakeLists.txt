file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${CONNECTION_LIB_NAME}/*.hpp")

# if any .cpp file appers, add it here, between existing variables
# add_library(${CONNECTION_LIB_NAME} ${HEADER_LIST})
add_library(${CONNECTION_LIB_NAME} INTERFACE)

# target_include_directories(${CONNECTION_LIB_NAME} PUBLIC ../include)
target_include_directories(${CONNECTION_LIB_NAME} INTERFACE ../include)

# target_compile_features(${CONNECTION_LIB_NAME} PUBLIC cxx_std_17)

target_link_libraries(${CONNECTION_LIB_NAME} INTERFACE
  sockpp
  commands1
)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
