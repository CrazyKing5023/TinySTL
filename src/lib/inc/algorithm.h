#ifndef _TINYSTL_ALGORITHM_H_
#define _TINYSTL_ALGORITHM_H_

#include <cstring>
#include <utility>

#include "allocator.h"
#include "type_traits.h"
#include "iterator.h"

namespace tinystl
{
    template <class ForwardIterator, class T>
    void fill(ForwardIterator first, ForwardIterator last, const T& value)
    {
        for (; first != last; ++first)
        {
            *first = value;
        }
    }
    inline void fill(char *first, char *last, const char& value)
    {
        memset(first, static_cast<unsigned char>(value), last - first;
    }
    
}
#endif
