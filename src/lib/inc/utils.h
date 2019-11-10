#ifndef TINYSTL_UTILS_H_
#define TINYSTL_UTILS_H_

namespace tinystl
{
    //*********** [swap] *********
    template <class T>
    void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }   
    
} // namespace tinystl

#endif