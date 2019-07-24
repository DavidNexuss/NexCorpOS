#include "stdafx.h"
#define ATEXIT_MAX_FUNCS	128

extern "C"{

    #include "memory/kmemory.h"
    #include "std/stdout.h"

	  void *__gxx_personality_v0;
  	  void *_Unwind_Resume;
	  void *__cxa_throw_bad_array_new_length;
}

/*
    New and delete operators.
 */
void *operator new(size_t size)
{
    return kmalloc(size);
}
 
void *operator new[](size_t size)
{
	print("Allocating array: ");
	printint(size);
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

extern "C"{

typedef unsigned uarch_t;
 
struct atexit_func_entry_t
{
	void (*destructor_func)(void *);
	void *obj_ptr;
	void *dso_handle;
};
 
int __cxa_atexit(void (*f)(void *), void *objptr, void *dso);
void __cxa_finalize(void *f);
void *__dso_handle = 0;

atexit_func_entry_t __atexit_funcs[ATEXIT_MAX_FUNCS];
uarch_t __atexit_func_count = 0;

int __cxa_atexit(void (*f)(void *), void *objptr, void *dso)
{
	if (__atexit_func_count >= ATEXIT_MAX_FUNCS) {return -1;};
	__atexit_funcs[__atexit_func_count].destructor_func = f;
	__atexit_funcs[__atexit_func_count].obj_ptr = objptr;
	__atexit_funcs[__atexit_func_count].dso_handle = dso;
	__atexit_func_count++;
	return 0;
};
 
void __cxa_finalize(void *f)
{
    println("Finalizing object");
	uarch_t i = __atexit_func_count;
	if (!f)
	{
		while (i--)
		{
			if (__atexit_funcs[i].destructor_func)
			{
				(*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
			}
		}
		return;
	}
 
	while (i--)
	{
		if (__atexit_funcs[i].destructor_func == f)
		{
			(*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
			__atexit_funcs[i].destructor_func = 0;
		}
	}
}
}