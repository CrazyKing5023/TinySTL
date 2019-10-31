//
// Created by jerry on 8/8/19.
//

#ifndef TINYSTL_VECTOR_H
#define TINYSTL_VECTOR_H

#include "allocator.h"
#include "type_traits.h"
#include "iterator.h"
#include <type_traits>

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
        typedef ptrdiff_t                   difference_type;

    private:
        iterator begin_;
        iterator end_;
        iterator endofStorage_;  

        typedef Alloc                       dataAllocator;
    public:
        //构造、复制、移动、析构函数
        vector() : begin_(0), end_(0), endofStorage_(0)
        {
            
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

        //比较操作相关
        bool operator == (const vector& v)const; //相等构造操作符
        bool operator != (const vector& v)const; //不等构造操作符

        //迭代器相关
        iterator begin()
        {
            return (begin_);
        }
        const_iterator begin() const
        {
            return (begin_);
        }
        const_iterator cbegin() const
        {
            return (begin_);
        }
        iterator end()
        {
            return (end_);
        }
        const_iterator end() const
        {
            return (end_);
        }
        const_iterator cend() const
        {
            return (end_);
        }
        reverse_iterator rbegin()
        {
            return reverse_iterator(end_);
        }
        const_reverse_iterator crbegin() const
        {
            return const_reverse_iterator(end_);
        }
        reverse_iterator rend()
        {
            return reverse_iterator(begin_);
        }
        const_reverse_iterator crend() const
        {
            return const_reverse_iterator(begin_);
        }

        //与容器相关
        difference_type size() const
        {
            return end_ - begin_;
        }
        difference_type capacity() const
        {
            return endofStorage_ - begin_;
        }
        bool empty() const
        {
            return begin_ = end_;
        }
        void resize(size_type n, value_type val = value_type());
        void reserve(size_type n);
        void shrink_to_fit();

        //访问元素相关
        reference operator[](const difference_type i)
        {
            return *(begin() + i);
        }
        const_reference operator[](const difference_type i) const
        {
            return *(cbegin() + i);
        }
        reference front()
        {
            return *(begin());
        }
        reference back()
        {
            return *(end() - 1);
        }
        pointer data()
        {
            return begin_;
        }

        //修改容器相关的操作
        //清空容器，销毁容器中的所有对象并使容器的size为０　但不回收容器已有的空间
        void clear();
        void swap(vector& v);
        void push_back(const value_type& value);
        void pop_back();
        iterator insert(iterator position, const value_type& val);
        void insert(iterator position, const size_type& n, const value_type& val);
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);

        //容器的空间配置器相关
        Alloc get_allocator()
        {
            return dataAllocator;
        }

    private:
        void destroyAndDeallocateAll();
        void allocateAndFillN(const size_type n, const value_type& value);
        template <class InputIterator>
        void allocateAndCopy(InputIterator first, InputIterator last);

        template <class InputIterator>
        void vector_aux(InputIterator first, InputIterator last, std::false_type);
        template <class Integer>
        void vector_aux(Integer n, const value_type& value, std::true_type);
        template <class InputIterator>
        void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
        template <class Integer>
        void insert_aux(iterator position, Integer n, const value_type& value, std::true_type);

        template <class InputIterator>
        void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
        void reallocateAndFillN(iterator position, const size_type& n, const value_type& val);
        size_type getNewCapacity(size_type len) const;

    public:
        template <class T, class Alloc>
        friend bool operator == (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
        template <class T, class Alloc>
        friend bool operator != (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
    };
    /*****************************************************************************************/
    // helper function

    
    
}




#endif //TINYSTL_VECTOR_H
