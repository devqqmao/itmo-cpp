# Add yours files here.
set(SRC_LIST
        tutorial/message.h
        tutorial/message.cpp)

add_library(${PROJECT_NAME}_lib ${SRC_LIST})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
