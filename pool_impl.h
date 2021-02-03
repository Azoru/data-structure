#ifndef POOL_IMPL_H
#define POOL_IMPL_H

#ifndef POOL_H
#include "pool.h"
#endif // POOL_H

#include <cstdlib>
#include <cstring>

template<typename T>
Pool<T>::Pool(uint32_t capacity)
    : _pool(NULL),
    _track(NULL),
    _free_list(0x00),
    _capacity(capacity) 
{
    _pool = (T*)malloc(sizeof(T) * _capacity);
    memset(_pool, 0x00, sizeof(T) * _capacity);

    _track = (uintptr_t*)malloc(sizeof(uintptr_t) * _capacity);
    for(size_t i = 0; i < _capacity; i++){
        _track[i] = (uintptr_t)(&_track[i + 1]);
    }
    _track[_capacity - 1] = 0x00;
    _free_list = (uintptr_t)(&_track[0]);
}


template<typename T>
Pool<T>::~Pool()
{
    free(_pool);
    free(_track);
}


template<typename T>
T* Pool<T>::alloc()
{
    if(0x00 == _free_list) return NULL;

    uintptr_t index = (_free_list - (uintptr_t)_track) / sizeof(uintptr_t);

    _free_list = _track[index];
    
    return &_pool[index];
}


template<typename T>
void Pool<T>::dealloc(T **data)
{
    T* ptr = *data;
    uintptr_t index = ((uintptr_t)ptr - (uintptr_t)_pool) / sizeof(T);

    memset(&_pool[index], 0x00, sizeof(T));
    
    _track[index] = _free_list;
    _free_list = (uintptr_t)(&_track[index]);

    *data = NULL;
}

#endif /* end of include guard: POOL_IMPL_H */
