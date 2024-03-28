cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(matrices)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(src)

option(MSE_BUILD_TESTS "Whether to build with tests" ON)

if (MSE_BUILD_TESTS)
    find_program(MSE_BASH bash)

    file(COPY ${CMAKE_CURRENT_LIST_DIR}/test DESTINATION ${CMAKE_BINARY_DIR})

    enable_testing()

    if (MSE_BASH)
        add_test(NAME ${PROJECT_NAME}_test
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test
                COMMAND ${MSE_BASH} ${CMAKE_CURRENT_SOURCE_DIR}/test/smoke_test.sh "$<TARGET_FILE:matrices>")
    endif()
endif()