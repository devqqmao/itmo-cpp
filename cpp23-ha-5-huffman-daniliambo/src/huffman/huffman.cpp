#include "huffman.h"
#include <iostream>

HuffmanConverter::HuffmanConverter(const char* inputFileName, const char* outputFileName)
    : inputFile_(inputFileName, std::ios::binary),
      outputFile_(outputFileName, std::ios::binary) {
    if (!inputFile_.is_open()) {
        throw std::invalid_argument("Input file doesn't exist");
    }
}

bool HuffmanConverter::Encode(const bool l) {
    Node* tree = BuildTree();
    if (tree == nullptr) {
        return true;
    }
    uint64_t inputFileSize = tree->weight_;

    std::unordered_map<std::vector<bool>, std::vector<bool>> codes = CreateCodes(tree);

    uint32_t addDataSize = 32;
    for (const std::pair<const std::vector<bool>, std::vector<bool>>& code : codes) {
        addDataSize += 16;
        addDataSize += code.second.size();
    }
    addDataSize += 64;
    addDataSize += 7;
    addDataSize /= 8;

    outputFile_.write(reinterpret_cast<char*>(&addDataSize), sizeof(addDataSize));

    uint8_t byte;
    BitBuffer bitBuffer;
    for (const std::pair<const std::vector<bool>, std::vector<bool>>& code : codes) {
        bitBuffer.Add(code.first);
        bitBuffer.Add(static_cast<uint8_t>(code.second.size() - 1));
        bitBuffer.Add(code.second);

        while (bitBuffer.Get(byte)) {
            outputFile_.write(reinterpret_cast<char*>(&byte), sizeof(byte));
            bitBuffer.Delete(sizeof(byte) * 8);
        }
    }
    if (bitBuffer.GetLast(byte)) {
        outputFile_.write(reinterpret_cast<char*>(&byte), sizeof(byte));
    }

    outputFile_.write(reinterpret_cast<char*>(&inputFileSize), sizeof(inputFileSize));

    Converter converter(codes);
    uint64_t compressedDataSize = 0;
    inputFile_.clear();
    inputFile_.seekg(0, std::ios::beg);
    inputFile_.read(reinterpret_cast<char*>(&byte), sizeof(byte));
    while (!inputFile_.eof()) {
        converter.Add(byte);

        while (converter.Get(byte)) {
            converter.Delete(8);
            outputFile_.write(reinterpret_cast<char*>(&byte), sizeof(byte));
            ++compressedDataSize;
        }

        inputFile_.read(reinterpret_cast<char*>(&byte), sizeof(byte));
    }
    if (converter.GetLast(byte)) {
        outputFile_.write(reinterpret_cast<char*>(&byte), sizeof(byte));
        ++compressedDataSize;
    }

    std::cout << inputFileSize << "\n";
    std::cout << compressedDataSize << "\n";
    std::cout << addDataSize << "\n";

    if (l) {
        std::unordered_map<std::vector<bool>, std::vector<bool>> reversedMap;
        for (const std::pair<const std::vector<bool>, std::vector<bool>>& code : codes) {
            reversedMap[code.second] = code.first;
        }

        PrintTable(reversedMap);
    }

    return true;
}

bool HuffmanConverter::Decode(const bool l) {
    uint32_t i;
    inputFile_.read(reinterpret_cast<char*>(&i), sizeof(i));
    if (inputFile_.eof()) {
        return true;
    }
    const uint32_t addDataSize = i;
    i -= 4;
    i -= 8;

    std::unordered_map<std::vector<bool>, std::vector<bool>> codes;
    BitBuffer bitBuffer;
    uint8_t byte;

    while (i != 0) {
        --i;
        inputFile_.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        bitBuffer.Add(byte);
    }

    while (bitBuffer.Size() > 8) {
        std::vector<bool> symbol(8);
        bitBuffer.Get(symbol, 8);
        bitBuffer.Delete(8);

        uint8_t len;
        bitBuffer.Get(len);
        ++len;
        bitBuffer.Delete(8);

        std::vector<bool> code(len);
        bitBuffer.Get(code, len);
        bitBuffer.Delete(len);

        codes[code] = symbol;
    }
    bitBuffer.Delete(bitBuffer.Size());

    uint64_t inputFileSize;
    inputFile_.read(reinterpret_cast<char*>(&inputFileSize), sizeof(inputFileSize));
    i = inputFileSize;

    Converter converter(codes);
    uint64_t compressedDataSize = 0;

    inputFile_.read(reinterpret_cast<char*>(&byte), sizeof(byte));
    while (!inputFile_.eof()) {
        ++compressedDataSize;
        converter.Add(byte);

        while (converter.Get(byte) && i != 0) {
            converter.Delete(8);
            outputFile_.write(reinterpret_cast<char*>(&byte), sizeof(byte));
            --i;
        }

        inputFile_.read(reinterpret_cast<char*>(&byte), sizeof(byte));
    }


    std::cout << compressedDataSize << "\n";
    std::cout << inputFileSize << "\n";
    std::cout << addDataSize << "\n";

    if (l) {
        PrintTable(codes);
    }

    return true;
}

void HuffmanConverter::PrintTable(const std::unordered_map<std::vector<bool>, std::vector<bool>>& codes) {
    BitBuffer bitBuffer;

    for (const std::pair<const std::vector<bool>, std::vector<bool>>& pair : codes) {
        for (bool bit : pair.first) {
            std::cout << (bit ? 1 : 0);
        }

        std::cout << "\t";

        uint8_t symbol;
        bitBuffer.Add(pair.second);
        bitBuffer.Get(symbol);
        bitBuffer.Delete(bitBuffer.Size());
        std::cout << static_cast<uint32_t>(symbol) << "\n";
    }
}

HuffmanConverter::Node* HuffmanConverter::BuildTree() {
    constexpr uint32_t codesCount = 256;

    std::vector<uint32_t> weights(codesCount, 0);

    std::uint8_t byte;
    inputFile_.read(reinterpret_cast<char*>(&byte), sizeof(byte));
    while (!inputFile_.eof()) {
        weights[byte]++;
        inputFile_.read(reinterpret_cast<char*>(&byte), sizeof(byte));
    }

    std::priority_queue<Node*, std::vector<Node*>, CompareNodePtr> priority_queue;

    for (uint32_t i = 0; i < weights.size(); i++) {
        if (weights[i] != 0) {
            priority_queue.push(new Node(i, weights[i]));
        }
    }

    while (priority_queue.size() > 1) {
        Node* firstMin = priority_queue.top();
        priority_queue.pop();

        Node* secondMin = priority_queue.top();
        priority_queue.pop();

        auto parent = new Node(0,
                               firstMin->weight_ + secondMin->weight_,
                               firstMin,
                               secondMin);

        priority_queue.push(parent);
    }

    Node* root = nullptr;
    if (!priority_queue.empty()) {
        root = priority_queue.top();
        priority_queue.pop();
    }

    return root;
}

std::unordered_map<std::vector<bool>, std::vector<bool>> HuffmanConverter::CreateCodes(Node* root) {
    std::unordered_map<std::vector<bool>, std::vector<bool>> result;
    BitBuffer bitBuffer;
    if (root->left_ == nullptr && root->right_ == nullptr) {
        bitBuffer.Add(root->code_);
        std::vector<bool> symbol;
        bitBuffer.Get(symbol, 8);
        bitBuffer.Delete(8);
        std::vector code = {true};
        result[symbol] = code;
        delete root;
        return result;
    }

    std::deque<std::vector<bool>> codes(1);
    std::deque nodes = {root};

    while (!nodes.empty()) {
        Node* node = nodes.front();
        nodes.pop_front();

        std::vector<bool> code = codes.front();
        codes.pop_front();

        if (node->left_ != nullptr) {
            nodes.push_back(node->left_);

            std::vector codeLeft(code);
            codeLeft.push_back(false);
            codes.push_back(codeLeft);
        }

        if (node->right_ != nullptr) {
            nodes.push_back(node->right_);

            std::vector codeRight(code);
            codeRight.push_back(true);
            codes.push_back(codeRight);
        }

        if (node->left_ == nullptr && node->right_ == nullptr) {
            bitBuffer.Add(node->code_);
            std::vector<bool> symbol;
            bitBuffer.Get(symbol, 8);
            bitBuffer.Delete(8);
            result[symbol] = code;
        }
    }

    delete root;
    return result;
}
