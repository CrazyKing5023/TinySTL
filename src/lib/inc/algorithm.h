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
        memset(first, static_cast<unsigned char>(value), last - first);
    }
    inline void fill(wchar_t *first, wchar_t *last, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
	}
	//********* [fill_n] ********************
	//********* [Algorithm Complexity: O(N)] ****************
	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}
	template<class Size>
	char *fill_n(char *first, Size n, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}
	template<class Size>
	wchar_t *fill_n(wchar_t *first, Size n, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}

    //*********** [max] ********************
	//********* [Algorithm Complexity: O(1)] ****************
	template <class T> 
	const T& max(const T& a, const T& b){
		return (a < b) ? b : a;
	}
	template <class T, class Compare>
	const T& max(const T& a, const T& b, Compare comp){
		return (comp(a, b)) ? b : a;
	}
	/*****************************************************************************************/
	// min 
	// 取二者中的较小值，语义相等时保证返回第一个参数
	/*****************************************************************************************/
	template <class T>
	const T& min(const T& lhs, const T& rhs)
	{
		return (lhs < rhs) ? lhs : rhs;
	}
	// 重载版本使用函数对象 comp 代替比较操作
	template <class T, class Compare>
	const T& min(const T& lhs, const T& rhs, Compare comp)
	{
		return (comp(lhs, rhs)) ? lhs : rhs; 
	}
	/*****************************************************************************************/
	// iter_swap
	// 将两个迭代器所指对象对调
	/*****************************************************************************************/
	template <class Iter1, class Iter2>
	void iter_swap(Iter1 lhs, Iter2 rhs)
	{

	}
	/*****************************************************************************************/
	// copy
	// 把 [first, last)区间内的元素拷贝到 [result, result + (last - first))内
	/*****************************************************************************************/
	// input_iterator_tag 版本
	
}
#endif
