#pragma once

#include <cstddef>
#include <vector>
#include <utility>

template <typename TType>
class Pool {
    public:
	    class Object;

		Pool() : _memory(nullptr), _capacity(0) {}

		~Pool()	{
			if (_memory != nullptr) {
				delete(_memory);
				_memory = nullptr;
			}
		}

        void resize(const size_t& numberOfObjectStored); // a faire

        template <typename... TArgs>
        Object acquire(TArgs&&... p_args); // a faire

    private:
		TType* getPtr(size_t index) { return (_memory + index); }

		void releaseObject(size_t index) {
			getPtr(index)->~TType();
			_freeIndices.push_back(index);
		}

        TType*				_memory;
        size_t				_capacity;
        std::vector<size_t>	_freeIndices;
};

template <typename TType>
class Pool<TType>::Object {
	public:
		Object() : _pool(nullptr), _index(0) {}

		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;

		Object(Object&& other) noexcept : _pool(other._pool), _index(other._index) {
			other._pool = nullptr;
		}

		Object& operator=(Object&& other) noexcept {
			if (this != &other)
			{
				release();
				_pool = other._pool;
				_index = other._index;

				other._pool = nullptr;
			}
			return (*this);
		}

		~Object() {
			release();
		}
		
		TType* operator->() {
			return( _pool->getPtr(_index));
		}
	
	private:
		friend class Pool<TType>;
		Object(Pool<TType>* pool, size_t index) : _pool(pool), _index(index) {}

		void release() {
			if (_pool != nullptr) {
				_pool->releaseObject(_index);
				_pool = nullptr;
			}
		}

		Pool<TType>*	_pool;
		size_t			_index;
};


template <typename TType>
void Pool<TType>::resize(const size_t& numberOfObjectStored) {
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