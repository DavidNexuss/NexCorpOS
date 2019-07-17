extern "C"{

    #include "kmemory.h"
}

void *operator new(size_t size)
{
    return kmalloc(size);
}
 
void *operator new[](size_t size)
{
    return kmalloc(size);
}
 
void operator delete(void *p)
{
    kfree(p);
}
 
void operator delete[](void *p)
{
    kfree(p);
}

void operator delete(void* p,unsigned int size_t){

    kfree(p);
}