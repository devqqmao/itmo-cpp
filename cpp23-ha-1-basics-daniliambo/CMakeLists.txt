cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(basics)

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