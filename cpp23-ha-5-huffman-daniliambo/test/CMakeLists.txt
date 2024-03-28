set(TEST_SRC_LIST
    test_example.cpp
        256_different_bytes.txt
        big_random.txt
        byte_code_0.txt
        byte_code_255.txt
        empty.txt
        example.txt
        Oliver_Twist.pdf
        one_byte.txt
        Prestuplenie-i-nakazanie.txt
        two_identical_bytes.txt
)

add_executable(${PROJECT_NAME}_tests ${TEST_SRC_LIST})
target_link_libraries(${PROJECT_NAME}_tests
    PRIVATE
        ${PROJECT_NAME}_lib
        Catch2::Catch2WithMain
)
target_include_directories(${PROJECT_NAME}_tests
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/../src"
)

catch_discover_tests(${PROJECT_NAME}_tests)