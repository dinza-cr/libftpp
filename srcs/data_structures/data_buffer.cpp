#include "libftpp.hpp"

DataBuffer::~DataBuffer() {
    _buffer.clear();
}

void DataBuffer::clear() {
    _buffer.clear();
    _readPos = 0;
}

DataBuffer& DataBuffer::operator<<(const std::string& str) {
    size_t len = str.size();
    *this << len;

    if (len > 0) {
        const uint8_t* raw = reinterpret_cast<const uint8_t*>(str.data());
        _buffer.insert(_buffer.end(), raw, raw + len);
    }
    return (*this);
}

DataBuffer& DataBuffer::operator>>(std::string& str) {
    size_t len = 0;
    *this >> len;

    if (_readPos + len > _buffer.size()) {
        throw std::runtime_error("DataBuffer: not enough data to read string");
    }

    str.assign(reinterpret_cast<const char*>(&_buffer[_readPos]), len);
    _readPos += len;
    return (*this);
}