#include "pool.h"
#include <cstdio>

struct Point{
    float x;
    float y;

    Point* init(float x, float y){
        this->x = x;
        this->y = y;
        return this;
    }
};

int main(int argc, char *argv[])
{
    Pool<Point> allocator(10000);

    Point *p = allocator.alloc()->init(10, 20); 
    printf("p = %p\np->x = %.2f, p->y = %.2f\n", p, p->x, p->y);

    Point *t = allocator.alloc()->init(30, 40);
    printf("t = %p\nt->x = %.2f, t->y = %.2f\n", t, t->x, t->y);
    allocator.dealloc(&t);

    p = allocator.alloc();
    printf("p = %p\np->x = %.2f, p->y = %.2f\n", p, p->x, p->y);

    return 0;
}
