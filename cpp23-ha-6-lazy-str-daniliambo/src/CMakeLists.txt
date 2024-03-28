# Add yours files here.
set(SRC_LIST lazy_string.hpp)

add_library(${PROJECT_NAME}_lib INTERFACE)
target_include_directories(${PROJECT_NAME}_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
