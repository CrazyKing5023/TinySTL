#ifndef _TINYSTL_ITERATOR_H_
#define _TINYSTL_ITERATOR_H_

#include <cstddef>
#include "type_traits.h"

namespace tinystl
{
    struct InputIteratorTag{};
    struct OutputIteratorTag{};
    struct ForwardIteratorTag : public InputIteratorTag{};
    struct BidirectionalIteratorTag : public ForwardIteratorTag{};
    struct RandomAccessIteratorTag : public BidirectionalIteratorTag{};

    template <class Category, class T, class Distance = ptrdiff_t,
              class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef Category        iterator_category;
        typedef T               value_type;
        typedef Distance        difference_type;
        typedef Pointer         pointer;
        typedef Reference       reference;
    };
    
    template <class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
    };
    
    //原生指针萃取偏特化
    template <class T>
    struct iterator_traits<T*>
    {
        typedef RandomAccessIteratorTag     iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };
    //原生 指向常量的指针　偏特化
    template <class T>
    struct iterator_traits<const T*>
    {
        typedef RandomAccessIteratorTag     iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
    };
    
    // 萃取某个迭代器的 category
    template <class Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator&)
    {
        typedef typename iterator_traits<Iterator>::iterator_category   category;
        return category();
    }

    template <class Iterator>
    inline typename iterator_traits<Iterator>::difference_type*
    distance_type(const Iterator&)
    {
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
    }

    template <class Iterator>
    inline typename iterator_traits<Iterator>::value_type*
    value_type(const Iterator&)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }

    template <class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    __distance(InputIterator first, InputIterator last, InputIteratorTag )
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }

    template <class RandomIterator>
    inline typename iterator_traits<RandomIterator>::difference_type
    __distance(RandomIterator first, RandomIterator last, RandomAccessIteratorTag )
    {
        return last - first;
    }

    template <class RandomIterator>
    inline typename iterator_traits<RandomIterator>::difference_type
    __distance(RandomIterator first, RandomIterator last, RandomAccessIteratorTag )
    {
        return last - first;
    }

    template <class InputIterator>
    inline typename iterator_traits<InputIterator>::difference
    distance(InputIterator first, InputIterator last)
    {
        typedef typename iterator_traits<InputIterator>::iterator_category category;
        return __distance(first, last, category());
    }

    //advance函数
    template <class InputIterator, class Distance>
    inline void __advance(InputIterator& i, Distance n, InputIteratorTag)
    {
        while (n--)
        {
            ++i;
        }
        
    }

    template <class BidirectionalIterator, class Distance>
    inline void __advance(BidirectionalIterator& i, Distance n, BidirectionalIteratorTag)
    {
        if (n >= 0)
        {
            while (n--)
            {
                ++i;
            }
        }
        else
        {
            while (n++)
            {
                --i;
            }   
        }  
    }

    template <class RandomAccessIterator, class Distance>
    inline void __advance(RandomAccessIterator& , Distance n, RandomAccessIteratorTag)
    {
        i += n;
    }

    template <class InputIterator, class Distance>
    inline void advance(InputIterator& i, Distance n)
    {
        __advance(i, n, iterator_category());
    }

/*****************************************************************************************/

// 模板类 : reverse_iterator
// 代表反向迭代器，使前进为后退，后退为前进
    template <class Iterator>
    class reverse_iterator
    {
    public:
        // 反向迭代器的五种相应型别
        typedef typename iterator_traits<Iterator>::itetator_category itetator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;
    
        typedef Iterator iterator_type;             //代表正向迭代器
        typedef reverse_iterator<Iterator> self;    //代表逆向迭代器
    private:
        
        Iterator current;
    public:
        //构造函数、析构函数、复制函数
        reverse_iterator() {}
        explicit reverse_iterator(iterator_type x) : current(x) {}
        reverse_iterator(const self& x) : current(x.current) {}

    public:
        //取出对应的正向迭代器
        iterator_type base() const
        {
            return current;
        }

        reference operator*() const
        {
            Iterator tmp = current;
            return *--tmp;
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        //前进(++)变成后退(--)
        self& operator++()
        {
            --current;
            return *this;
        }

        self operator++(int)
        {
            self tmp = *this;
            --current;
            return tmp;
        }

        //后退(--)变成前进(++)
        self& operator--()
        {
            ++current;
            return *this;
        }

        self operator--(int)
        {
            self tmp = *this;
            ++current;
            return tmp;
        }

        //前进与后退方向完全逆转
        self operator+(difference_type n) const
        {
            return self(current - n);
        }

        self$ operator+=(difference_type n)
        {
            current -= n;
            return *this;
        }

        self operator-(difference_type n) const
        {
            return self(current + n);
        }

        self& operator-=(difference_type n)
        {
            current += n;
            return *this;
        }

        reference operator[](difference_type n) const
        {
            return *(*this + n);
        }
    };

    // 重载 operator-
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator>& lhs,
              const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() - rhs.base();
    }

    // 重载 operator+
    template <class Iterator>
    reverse_iterator<Iterator> operator+(
        typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator>& lhs)
    {
        return lhs + n;
    }


    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
    {
        return !(lhs > lhs);
    }

    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
    {
        return !(lhs < rhs);
    }
}

#endif