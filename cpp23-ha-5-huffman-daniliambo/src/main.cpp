#include <cstring>

#include "huffman/huffman.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if ((argc != 5 || strcmp(argv[1], "-v") != 0) && argc != 4) {
        std::cerr << "Wrong count of arguments";
        return 0;
    }

    // if (strcmp(argv[0], "huffman") == 0) {
    //     std::cerr << "Wrong command";
    //     return 0;
    // }

    bool v = false;
    uint32_t i = 1;
    if (argc == 5 && strcmp(argv[1], "-v") == 0) {
        v = true;
        i = 2;
    }

    HuffmanConverter huffman_converter(argv[i + 1], argv[i + 2]);

    if (strcmp(argv[i], "-c") == 0) {
        huffman_converter.Encode(v);
    }
    else if (strcmp(argv[i], "-d") == 0) {
        huffman_converter.Decode(v);
    }
    else {
        std::cerr << "Wrong mode";
        return 0;
    }
}
