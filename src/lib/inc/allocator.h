#ifndef TINYSTL_ALLOCATOR_H__
#define TINYSTL_ALLOCATOR_H__
#include <cstdlib>
#include <cassert>
#include <new>
#include <cstddef>

namespace tinystl
{
    template <class T>
    class allocator
    {
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;

    public:

        static T*   allocate();
        static T*   allocate(size_type n);

        static void deallocate(T *ptr);
        static void deallocate(T *ptr, size_type n);

        static void construct(T *ptr);
        static void construct(T *ptr, const T& value);
       

        static void destroy(T *ptr);
        static void destroy(T *first, T *last);
    };
    
    template <class T>
    T* allocator<T>::allocate()
    {
        return static_cast<T*>(::operator new(sizeof(T)));
    }

    template <class T>
    T* allocator<T>::allocate(size_type n)
    {
        if (0 == n)
        {
            return nullptr;
        }
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    template <class T>
    void allocator<T>::deallocate(T *ptr)
    {
        if (nullptr == ptr)
        {
            return ;
        }
        ::operator delete(ptr);
    }

    template <class T>
    void allocator<T>::deallocate(T *ptr, size_type n)
    {
        if (nullptr == ptr)
        {
            return ;
        }
        ::operator delete(ptr);
    }
    
    template <class T>
    void allocator<T>::construct(T *ptr)
    {
        new(ptr)T();
    }

    template <class T>
    void allocator<T>::construct(T *ptr, const T& value)
    {
        new(ptr)T(value);
    }

    template <class T>
    void allocator<T>::destroy(T *ptr)
    {
        ptr->~T();
    }

    template <class T>
    void allocator<T>::destroy(T *first, T *last)
    {
        for (; first != last; first ++)
        {
            first->~T();
        }
    }

}
#endif