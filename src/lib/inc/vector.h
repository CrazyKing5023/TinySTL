//
// Created by jerry on 8/8/19.
//

#ifndef TINYSTL_VECTOR_H
#define TINYSTL_VECTOR_H

#include "allocator.h"
#include "type_traits.h"
#include "iterator.h"

namespace tinystl
{
    template <class T, class Alloc = allocator<T>>
    class vector
    {
    public:
        //vector 的嵌套型别定义
        typedef T                           value_type;
        typedef T*                          iterator;
        typedef const T*                    const_iterator;
        typedef reverse_iterator<T*>        reverse_iterator;    
        typedef reverse_iterator<const T*>  const_reverse_iterator;
        typedef iterator                    pointer;
        typedef T&                          reference;
        typedef const T&                    const_reference;
        typedef size_t                      size_type;
        typedef ptrdiff_t                   dfference_type;

    private:
        iterator begin_;
        iterator end_;
        iterator cap_;  

    public:
        //构造、复制、移动、析构函数
        vector() noexcept
        {
            try_init();
        }

        explicit vector(size_type n)
        {

        }

        vector(const size_type n, const value_type& value);
        
        template <class Iter>
        vector(Iter first, Iter last);
        vector(const vector& v);
        vector(vector&& v);
        vector& operator = (const vector& v);
        vector& operator = (vector&& v);
        ~vector();
    };
    /*****************************************************************************************/
    // helper function

    template <class T>
    void vector<T>::try_init() noexcept
    {
        
    }
}




#endif //TINYSTL_VECTOR_H
