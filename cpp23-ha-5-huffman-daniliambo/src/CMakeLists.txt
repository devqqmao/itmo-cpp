# Add yours files here.
set(SRC_LIST
    huffman/huffman.cpp
    huffman/huffman.h)
add_library(${PROJECT_NAME}_lib ${SRC_LIST})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
