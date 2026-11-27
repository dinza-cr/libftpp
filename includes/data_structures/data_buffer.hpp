#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <string>
#include <stdexcept>
#include <type_traits>

class DataBuffer {
    public:
        DataBuffer() : _readPos(0) {}
        ~DataBuffer();

        void clear();
        size_t size() const { return (_buffer.size()); }
        const std::vector<uint8_t>& getBuffer() const { return (_buffer); }

        template <typename TType>
        DataBuffer& operator<<(const TType& data);

        template <typename TType>
        DataBuffer& operator>>(TType& data);

        DataBuffer& operator<<(const std::string& str);
        DataBuffer& operator>>(std::string& str);

    private:
        std::vector<uint8_t>    _buffer;
        size_t                  _readPos;
} ;

#include "data_buffer.tpp"