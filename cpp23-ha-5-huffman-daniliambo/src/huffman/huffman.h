#pragma once
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <queue>


// Compressed file header structure:
//      uint32_t -- additionalDataSize
//
//      uint8_t -- symbol, uint8_t -- len-1, nbit -- code
//      .
//      .
//      .
//      uint8_t -- symbol, uint8_t -- len-1, nbit -- code
//
//      uint64_t -- inputFileSize

class HuffmanConverter {
    struct Node {
        explicit Node(const uint8_t code,
                      const uint64_t weight = 0,
                      Node* left = nullptr,
                      Node* right = nullptr)
            : code_(code),
              weight_(weight),
              left_(left),
              right_(right) { }

        ~Node() {
            delete left_;
            delete right_;
        }

        const uint8_t code_;
        uint64_t weight_;
        Node* left_;
        Node* right_;
    };

    struct CompareNodePtr {
        bool operator()(const Node* left, const Node* right) const {
            return left->weight_ > right->weight_;
        }
    };

    class BitBuffer {
    public:
        template<std::integral T>
        void Add(T bytes) {
            constexpr uint32_t bitCount = sizeof(T) * 8;

            for (int64_t i = bitCount - 1; i >= 0; --i) {
                if ((bytes & 1 << i) >> i == 1) {
                    buffer_.push_back(true);
                }
                else {
                    buffer_.push_back(false);
                }
            }
        }

        void Add(const std::vector<bool>& buffer) {
            buffer_.insert(buffer_.end(), buffer.begin(), buffer.end());
        }

        bool Get(bool& bit, const uint32_t index) const {
            if (buffer_.size() <= index) {
                return false;
            }

            bit = buffer_[index];
            return true;
        }

        bool Get(std::vector<bool>& bits, const uint32_t count) const {
            if (buffer_.size() < count) {
                return false;
            }

            bits.assign(buffer_.begin(), buffer_.begin() + count);
            return true;
        }

        template<std::integral T>
        bool Get(T& bytes) const {
            constexpr uint32_t bitCount = sizeof(T) * 8;

            if (buffer_.size() < bitCount) {
                return false;
            }

            bytes = 0;
            for (uint64_t i = 0; i < bitCount; i++) {
                bytes <<= 1;
                if (buffer_[i]) {
                    bytes += 1;
                }
            }

            return true;
        }

        template<std::integral T>
        bool GetLast(T& bytes) const {
            constexpr uint32_t bitCount = sizeof(T) * 8;
            const uint32_t bufferSize = buffer_.size();

            if (buffer_.empty() || bufferSize >= bitCount) {
                return false;
            }

            bytes = 0;
            for (uint64_t i = 0; i < bufferSize; i++) {
                bytes <<= 1;
                if (buffer_[i]) {
                    bytes += 1;
                }
            }
            bytes <<= bitCount - bufferSize;

            return true;
        }

        void Delete(const uint32_t size) {
            const uint32_t bufferSize = buffer_.size();

            for (uint32_t i = 0; i < size && i < bufferSize; i++)
                buffer_.pop_front();
        }

        [[nodiscard]] uint64_t Size() const {
            return buffer_.size();
        }

    private:
        std::deque<bool> buffer_;
    };

    class Converter {
    public:
        explicit Converter(std::unordered_map<std::vector<bool>, std::vector<bool>> codes)
            : codes_(std::move(codes)) { }

        template<std::integral T>
        void Add(T bytes) {
            data_.Add(bytes);

            std::vector<bool> unencodedData;
            uint32_t i = 0;
            bool bit;
            while (data_.Get(bit, i)) {
                unencodedData.push_back(bit);
                if (codes_.contains(unencodedData)) {
                    encodeData_.Add(codes_[unencodedData]);

                    data_.Delete(i + 1);
                    unencodedData.clear();
                    i = 0;
                }
                else {
                    ++i;
                }
            }
        }

        template<std::integral T>
        bool Get(T& bytes) const {
            return encodeData_.Get(bytes);
        }

        template<std::integral T>
        bool GetLast(T& bytes) const {
            return encodeData_.GetLast(bytes);
        }

        void Delete(const uint32_t size) {
            encodeData_.Delete(size);
        }

    private:
        BitBuffer data_;
        std::unordered_map<std::vector<bool>, std::vector<bool>> codes_;
        BitBuffer encodeData_;
    };

public:
    HuffmanConverter(const char* inputFileName, const char* outputFileName);

    bool Encode(bool l);

    bool Decode(bool l);

    void PrintTable(const std::unordered_map<std::vector<bool>, std::vector<bool>>& codes);

private:
    Node* BuildTree();

    std::unordered_map<std::vector<bool>, std::vector<bool>> CreateCodes(Node* root);

    std::ifstream inputFile_;
    std::ofstream outputFile_;
};
