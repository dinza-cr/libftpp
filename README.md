# libftpp
A library implementing advanced C++ concepts.

## Compilation with main
c++ -Wall -Wextra -Werror -std=c++11 -I. tests/ libftpp.a

## Library content

### Data structures

#### Pool
An **Object Pool** (`Pool<TType>`) designed to pre-allocate a contiguous block of raw memory (`::operator new`) and reuse object instances without repeated heap allocations or deallocations.
* **`resize(size_t)`**: Allocates raw memory capacity without invoking constructors, maintaining a stack of available slot indices in $O(1)$.
* **`acquire(TArgs&&...)`**: Constructs an object in-place at an available memory slot using *placement new* and perfect forwarding (`std::forward`), returning a move-only RAII wrapper (`Pool<TType>::Object`).
* **`Pool::Object`**: Automatically calls the object's destructor (`~TType()`) and returns its slot to the pool when going out of scope, accessible via `operator->`.

#### Data buffer
A binary serialization container (`DataBuffer`) that stores heterogeneous data types as a sequential byte stream (`std::vector<uint8_t>`).
* **Stream Operators (`<<` / `>>`)**: Supports chained serialization and deserialization using C++ stream syntax (`buf << a << b; buf >> a >> b;`).
* **Type Safety**: Uses compile-time checks (`std::is_trivially_copyable`) for raw byte copying of primitive types and POD structures, alongside dedicated overloads for variable-length types like `std::string` (length-prefixed encoding) with bounds checking on read.