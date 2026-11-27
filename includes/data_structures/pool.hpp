#pragma once

#include <cstddef>
#include <vector>
#include <utility>
#include <stdexcept>

template <typename TType>
class Pool {
    public:
	    class Object;

		Pool() : _memory(nullptr), _capacity(0) {}
		~Pool();

        void resize(const size_t& numberOfObjectStored);

        template <typename... TArgs>
        Object acquire(TArgs&&... p_args);

		Pool(const Pool&) = delete;
		Pool& operator=(const Pool&) = delete;

    private:
		TType* getPtr(size_t index) { return (_memory + index); }

		void releaseObject(size_t index) ;

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

		Object(Object&& other) noexcept : _pool(other._pool), _index(other._index) { other._pool = nullptr; }

		Object& operator=(Object&& other) noexcept ;

		~Object() { release(); }
		
		TType* operator->() { return( _pool->getPtr(_index)); }
	
	private:
		friend class Pool<TType>;
		Object(Pool<TType>* pool, size_t index) : _pool(pool), _index(index) {}

		void release();

		Pool<TType>*	_pool;
		size_t			_index;
};

#include "pool.tpp"