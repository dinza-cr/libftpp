#pragma once

template <typename TType>
DataBuffer& DataBuffer::operator<<(const TType& data) {
    static_assert(std::is_trivially_copyable<TType>::value, "Type must be trivially copyable");
    const uint8_t* raw = reinterpret_cast<const uint8_t*>(&data);
    _buffer.insert(_buffer.end(), raw, raw + sizeof(TType));
    return (*this);
}

template <typename TType>
DataBuffer& DataBuffer::operator>>(TType& data) {
    static_assert(std::is_trivially_copyable<TType>::value, "Type must be trivially copyable");
    if (_readPos + sizeof(TType) > _buffer.size()) {
        throw std::runtime_error("DataBuffer: not enough data to read");
    }
    std::memcpy(&data, &_buffer[_readPos], sizeof(TType));
    _readPos += sizeof(TType);
    return (*this);
}