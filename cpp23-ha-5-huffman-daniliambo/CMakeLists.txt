cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(huffman)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(test/256_different_bytes.txt ${CMAKE_CURRENT_BINARY_DIR}/test/256_different_bytes.txt COPYONLY)
configure_file(test/big_random.txt ${CMAKE_CURRENT_BINARY_DIR}/test/big_random.txt COPYONLY)
configure_file(test/byte_code_0.txt ${CMAKE_CURRENT_BINARY_DIR}/test/byte_code_0.txt COPYONLY)
configure_file(test/byte_code_255.txt ${CMAKE_CURRENT_BINARY_DIR}/test/byte_code_255.txt COPYONLY)
configure_file(test/empty.txt ${CMAKE_CURRENT_BINARY_DIR}/test/empty.txt COPYONLY)
configure_file(test/example.txt ${CMAKE_CURRENT_BINARY_DIR}/test/example.txt COPYONLY)
configure_file(test/Oliver_Twist.pdf ${CMAKE_CURRENT_BINARY_DIR}/test/Oliver_Twist.pdf COPYONLY)
configure_file(test/one_byte.txt ${CMAKE_CURRENT_BINARY_DIR}/test/one_byte.txt COPYONLY)
configure_file(test/Prestuplenie-i-nakazanie.txt ${CMAKE_CURRENT_BINARY_DIR}/test/Prestuplenie-i-nakazanie.txt COPYONLY)
configure_file(test/two_identical_bytes.txt ${CMAKE_CURRENT_BINARY_DIR}/test/two_identical_bytes.txt COPYONLY)

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
    # From https://github.com/catchorg/Catch2/blob/v3.1.0/docs/cmake-integration.md#top
    Include(FetchContent)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v3.1.0
    )
    FetchContent_MakeAvailable(Catch2)

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    include(CTest)
    include(Catch)

    add_subdirectory(test)
endif()