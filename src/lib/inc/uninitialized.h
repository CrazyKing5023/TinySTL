#ifndef _TINYSTL_UNINITIALIZED_H_
#define _TINYSTL_UNINITIALIZED_H_

#include "allocator.h"
#include "type_traits.h"
#include "iterator.h"
#include "algorithm.h"

namespace tinystl
{
    /***************************************************************************/
    template <class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
        ForwardIterator result, __ture_type);

    template <class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
        ForwardIterator result, __false_type);

    template <class InputIterator, class ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
    {
        typedef typename _type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type isPODType;
        return _uninitialized_copy_aux(first, last, result, isPODType());
    }

    template <class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
        ForwardIterator result, __ture_type)
    {
        memcpy(result, first, (last - first) * sizeof(*first));
        return result + (last - first);
    }

    template <class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
        ForwardIterator result, __false_type)
    {
        int i = 0;
        for (; first != last; ++first, ++i)
        {
            construct((result + i), *first);
        }
    }

    /***************************************************************************/
    template <class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
        const T& value, __ture_type);

    template <class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
        const T& value, __false_type);

    template <class ForwardIterator, class T>
    void uninitialized_fill(ForwardIterator first, ForwardIterator last,
        const T& value)
    {
        typedef typename _type_traits<T>::is_POD_type isPODType;
        _uninitialized_fill_aux(first, last, value, isPODType);
    }
    template <class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
        const T& value, __ture_type)
    {
        fill(first, last, value);
    }
    template <class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
        const T& value, __false_type)
    {
        for (; first != last; ++first)
        {
            construct(first, value);
        }
    }

    /***************************************************************************/
    template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
		Size n, const T& x, __ture_type);
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
		Size n, const T& x, __false_type);

	template<class ForwardIterator, class Size, class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first,
		Size n, const T& x){
		typedef typename _type_traits<T>::is_POD_type isPODType;
		return _uninitialized_fill_n_aux(first, n, x, isPODType());
	}
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
		Size n, const T& x, __ture_type){
		return fill_n(first, n, x);
	}
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
		Size n, const T& x, __false_type){
		int i = 0;
		for (; i != n; ++i){
			construct((T*)(first + i), x);
		}
		return (first + i);
	}
}

#endif