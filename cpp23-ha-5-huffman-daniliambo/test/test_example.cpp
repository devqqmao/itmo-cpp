#include <catch2/catch_test_macros.hpp>

#include <huffman/huffman.h>
#include <iostream>
#include <string>
#include <fstream>

void EncodeDecode(const std::string& baseName, const std::string& format = ".txt") {
    const std::string inputFile = baseName + format;
    const std::string compressedFile = baseName + "(compressed).bin";
    const std::string decompressedFile = baseName + "(new)" + format;
    
    HuffmanConverter huffman_converter(inputFile.data(), compressedFile.data());
    huffman_converter.Encode(false);
    huffman_converter = HuffmanConverter(compressedFile.data(), decompressedFile.data());
    huffman_converter.Decode(false);
}

bool CompareTwoFiles(const std::string& baseName) {
    const std::string inputFile = baseName + ".txt";
    const std::string compressedFile = baseName + "(compressed).bin";
    const std::string decompressedFile = baseName + "(new).txt";
    
    std::ifstream in_file(inputFile, std::ios::binary);
    std::ifstream out_file(decompressedFile, std::ios::binary);
    return std::equal(std::istreambuf_iterator(in_file), std::istreambuf_iterator<char>(), std::istreambuf_iterator(out_file));
}

TEST_CASE("Empty file", "[huffman]") {
    const std::string baseName = "empty";

    EncodeDecode(baseName);
    bool result = CompareTwoFiles(baseName);

    REQUIRE(result);
}

TEST_CASE("One byte file", "[huffman]") {
    const std::string baseName = "one_byte";

    EncodeDecode(baseName);
    bool result = CompareTwoFiles(baseName);

    REQUIRE(result);
}

TEST_CASE("Zero code file", "[huffman]") {
    const std::string baseName = "byte_code_0";

    EncodeDecode(baseName);
    bool result = CompareTwoFiles(baseName);

    REQUIRE(result);
}

TEST_CASE("255 code file", "[huffman]") {
    const std::string baseName = "byte_code_255";

    EncodeDecode(baseName);
    bool result = CompareTwoFiles(baseName);

    REQUIRE(result);
}

TEST_CASE("all 256 codes file", "[huffman]") {
    const std::string baseName = "256_different_bytes";

    EncodeDecode(baseName);
    bool result = CompareTwoFiles(baseName);

    REQUIRE(result);
}

TEST_CASE("Only 2 same bytes", "[huffman]") {
    const std::string baseName = "two_identical_bytes";

    EncodeDecode(baseName);
    bool result = CompareTwoFiles(baseName);

    REQUIRE(result);
}

TEST_CASE("Big file txt", "[huffman]") {
    const std::string baseName = "Prestuplenie-i-nakazanie";

    EncodeDecode(baseName);
    bool result = CompareTwoFiles(baseName);

    REQUIRE(result);
}

TEST_CASE("Binary big file", "[huffman]") {
    const std::string baseName = "Oliver_Twist";

    EncodeDecode(baseName, ".pdf");
    bool result = CompareTwoFiles(baseName);

    REQUIRE(result);
}

TEST_CASE("Big file with random text", "[huffman]") {
    const std::string baseName = "big_random";

    EncodeDecode(baseName);
    bool result = CompareTwoFiles(baseName);

    REQUIRE(result);
}

TEST_CASE("Example file", "[huffman]") {

    const std::string baseName = "example";
    constexpr uint32_t inputFileSizeCorrect = 15;
    constexpr uint32_t compressedDataSizeCorrect = 5;

	uint32_t inputFileSize;
    uint32_t compressedDataSize;

	std::streambuf* bak = std::cout.rdbuf();
    std::ofstream output("sizes.txt", std::ios::out);
    std::cout.rdbuf(output.rdbuf());

    EncodeDecode(baseName);
    bool result = CompareTwoFiles(baseName);

	std::cout.rdbuf(bak);
    output.close();
    std::ifstream input("sizes.txt", std::ios::in);

	input >> inputFileSize;
	input >> compressedDataSize;

    REQUIRE(result);
    REQUIRE(inputFileSizeCorrect == inputFileSize);
    REQUIRE(compressedDataSizeCorrect == compressedDataSize);
}