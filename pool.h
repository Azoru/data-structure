#ifndef POOL_H
#define POOL_H

#include <stdint.h>

template<typename T>
class Pool{
    public:
        explicit 
            Pool(uint32_t capacity);
        ~Pool();
        T*       alloc();
        void     dealloc(T**data);
    private:
        T         *_pool;
        uintptr_t *_track;
        uintptr_t  _free_list;

        uint32_t   _capacity; 
};

#ifndef POOL_IMPL_H
#include "pool_impl.h"
#endif // POOL_IMPL_H

#endif /* end of include guard: POOL_H */
