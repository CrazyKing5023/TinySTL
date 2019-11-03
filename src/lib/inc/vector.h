//
// Created by jerry on 8/8/19.
//

#ifndef TINYSTL_VECTOR_H
#define TINYSTL_VECTOR_H

#include "allocator.h"
#include "type_traits.h"
#include "iterator.h"
#include "uninitialized.h"
#include <type_traits>

namespace tinystl
{
    template <class T, class Alloc = allocator<T>>
    class vector
    {
    public:
        //vector 的嵌套型别定义
        typedef T                                       value_type;
        typedef T*                                      iterator;
        typedef const T*                                const_iterator;
        typedef tinystl::reverse_iterator<T*>           reverse_iterator;    
        typedef tinystl::reverse_iterator<const T*>     const_reverse_iterator;
        typedef iterator                                pointer;
        typedef T&                                      reference;
        typedef const T&                                const_reference;
        typedef size_t                                  size_type;
        typedef ptrdiff_t                               difference_type;

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

    template <class T, class Alloc>
    vector<T, Alloc>::~vector()
    {
        destroyAndDeallocateAll();
    }
    template <class T, class Alloc>
    vector<T, Alloc>::vector(const size_type n)
    {
        allocateAndFillN(n, value_type());
    }
    template <class T, class Alloc>
    vector<T, Alloc>::vector(const size_type n, const value_type& value)
    {
        allocateAndFillN(n ,value);
    }
    template <class T, class Alloc>
    template <class InputIterator>
    vector<T, Alloc>::vector(InputIterator first, InputIterator last)
    {
        vector_aux(first, last, typename std::is_integral<InputIterator>::type());
    }
    template <class T, class Alloc>
    vector<T, Alloc>::vector(const vector& v) //copy construct function
    {
        allocateAndCopy(v.begin_, v.end_);
    }
    template <class T, class Alloc>
    vector<T, Alloc>::vector(vector&& v) //right value reference 
    {
        begin_  = v.begin_;
        end_    = v.end_;
        endofStorage_ = v.endofStorage_;
        v.begin_ = v.end_ = v.endofStorage_ = 0;
    }
    template <class T, class Alloc>
    vector<T, Alloc>& vector<T, Alloc>::operator = (const vector& v)
    {
        if (this != &v)
        {
            allocateAndCopy(v.begin_, v.end_);
        }
        return *this;
    }
    template <class T, class Alloc>
    vector<T, Alloc>& vector<T, Alloc>::operator = (vector&& v)
    {
        if (this != &v)
        {
            destroyAndDeallocateAll();
            begin_ = v.begin_;
            end_   = v.end_;
            endofStorage_ = v.endofStorage_;
            v.begin_ = v.end_ = v.endofStorage_ = 0;
        }
        return *this;
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::resize(size_type n, value_type val = value_type())
    {
        if (n < size())
        {
            dataAllocator::destroy(begin_ + n, end_);
            end_ = begin_ + n;
        }
        else if(n > size() && n <= capacity())
        {
            auto lengthOfInsert = n - size();
            end_ = tinystl::uninitialized_fill_n(begin_, lengthOfInsert, val);
        }
        else if(n > capacity())
        {
            auto lengthOfInsert = n - size();
            T *newStart = dataAllocator::allocate(getNewCapacity(lengthOfInsert));
            T *newFinish = tinystl::uninitialized_copy(begin(), end(), newStart);
            newFinish = tinystl::uninitialized_fill_n(newFinish, lengthOfInsert, val);

            destroyAndDeallocateAll();
            begin_ = newStart;
            end_ = newFinish;
            endofStorage_ = begin_ + n;
        }
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::reserve(size_type n)
    {
        if (n < capacity())
            return;
        T *newStart = dataAllocator::allocate(n);
        T *newFinish = tinystl::uninitialized_copy(begin(), end(), newStart);
        destroyAndDeallocateAll();
        
        begin_ = newStart;
        end_    = newFinish;
        endofStorage_ = begin_ + n;
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position)
    {
        return erase(position, position + 1);
    }
    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
    {
        difference_type lenOfTail = end() - last;
        difference_type lenOfRemoved = last - first;
        end_ = end_ - lenOfRemoved;
        for (; lenOfTail != 0; --lenOfTail)
        {
            auto temp = (last - lenOfRemoved);
            *temp = *(last++);
        }
        return (first);
    }

    template <class T, class Alloc>
    template <class InputIterator>
    void vector<T, Alloc>::reallocateAndCopy(iterator position, InputIterator first, InputIterator last)
    {
        difference_type newCapacity = getNewCapacity(last - first);

        T *newStart = dataAllocator::allocate(newCapacity);
        T *newEndOfStorage = newStart + newCapacity;
        T *newFinish = tinystl::uninitialized_copy(begin(), position, newStart);
        newFinish = tinystl::uninitialized_copy(first, last, newFinish);
        newFinish = tinystl::uninitialized_copy(position, end(), newFinish);

        destroyAndDeallocateAll();
        begin_ = newStart;
        end_ = newFinish;
        endofStorage_ = newEndOfStorage;
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::reallocateAndFillN(iterator position, const size_type& n, const value_type& val)
    {
        difference_type newCapacity = getNewCapacity(n);

        T *newStart = dataAllocator::allocate(newCapacity);
        T *newEndOfStorage = newStart + newCapacity;
        T *newFinish = tinystl::uninitialized_copy(begin(), position, newStart);

        newFinish = tinystl::uninitialized_fill_n(newFinish, n, val);
        newFinish = tinystl::uninitialized_copy(position, end(), newFinish);

        destroyAndDeallocateAll();
        begin_ = newStart;
        end_ = newFinish;
        endofStorage_ = newEndOfStorage;
    }
    template <class T, class Alloc>
    template <class InputIterator>
    void vector<T, Alloc>::insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type)
    {
        difference_type locationLeft = endofStorage_ - end_;

        difference_type locationNeed = distance(first, last);

        if (locationLeft >= locationNeed)
        {
            if (end_ - position > locationNeed)
            {
                tinystl::uninitialized_copy(end_ - locationNeed, end_, end_);
                std::copy_backward(position, end_ - locationNeed, end_);
                std::copy(first, last, position);
            }
            else
            {
                iterator temp = tinystl::uninitialized_copy(first + (end_ - position), last, end_);
                tinystl::uninitialized_copy(position, end_, temp);
                std::copy(first, first + (end_ - position), position);
            }
            end_ += locationNeed;
            
        }
        else
        {
            reallocateAndCopy(position, first, last);
        }
    }

    
}




#endif //TINYSTL_VECTOR_H
