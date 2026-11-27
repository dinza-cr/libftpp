#pragma once


//Pool 
template <typename TType>
Pool<TType>::~Pool() {
	if (_memory != nullptr) {
		::operator delete(_memory);
		_memory = nullptr;
	}
}

template <typename TType>
void Pool<TType>::releaseObject(size_t index) {
	getPtr(index)->~TType();
	_freeIndices.push_back(index);
}


template <typename TType>
void Pool<TType>::resize(const size_t& numberOfObjectStored) {
    if (_freeIndices.size() != _capacity) {
        throw std::runtime_error("Cannot resize Pool while objects are still acquired");
    }
    
    if (_memory != nullptr) {
        ::operator delete(_memory);
        _memory = nullptr;
        _freeIndices.clear();
        _capacity = 0;
    }

    if (numberOfObjectStored > 0) {
        _memory = static_cast<TType*>(::operator new(numberOfObjectStored * sizeof(TType)));
        _capacity = numberOfObjectStored;
        _freeIndices.reserve(numberOfObjectStored);
        for (size_t i = 0; i < numberOfObjectStored; ++i) {
            _freeIndices.push_back(i);
        }
    }
}

template <typename TType>
template <typename... TArgs>
typename Pool<TType>::Object Pool<TType>::acquire(TArgs&&... p_args) {
    if (_freeIndices.empty()) {
        throw std::runtime_error("No available objects in pool");
    }

    size_t index = _freeIndices.back();
    _freeIndices.pop_back();

    try {
        new (getPtr(index)) TType(std::forward<TArgs>(p_args)...);
    } catch (...) {
        _freeIndices.push_back(index);
        throw;
    }

    return (Object(this, index));
}



//Object
template <typename TType>
typename Pool<TType>::Object& Pool<TType>::Object::operator=(Object&& other) noexcept {
	if (this != &other)
	{
		release();
		_pool = other._pool;
		_index = other._index;

		other._pool = nullptr;
	}
	return (*this);
}

template <typename TType>
void Pool<TType>::Object::release() {
	if (_pool != nullptr) {
		_pool->releaseObject(_index);
		_pool = nullptr;
	}
}