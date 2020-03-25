#ifndef TINYSTL_LIST_H
#define TINYSTL_LIST_H

#include "iterator.h"

namespace tinystl
{
template <class T>
struct _list_node
{
    _list_node *prev;
    _list_node *next;
    T data;

    
};


template <class T, class Ref, class Ptr>
struct _list_iterator
{
    typedef _list_iterator<T, T&, T*>       iterator;
    typedef _list_iterator<T, Ref, Ptr>     self;

    typedef BidirectionalIteratorTag        iterator_category;
    typedef T                               value_type;
    typedef Ptr                             pointer;
    typedef Ref                             reference;
    typedef _list_node<T>                   *link_type;
    typedef size_t                          size_type;
    typedef ptrdiff_t                       difference_type;

    link_type                               node;

    //constructor
    _list_iterator(link_type x) : node(x) {}
    _list_iterator() {}
    _list_iterator(const iterator &x) : node(x.node) {}

    bool operator==(const self &x) const
    {
        return node == x.node;
    }
    
    bool operator!=(const self &x) const
    {
        return node != x.node;
    }

    reference operator*() const
    {
        return (*node).data;
    }

    pointer operator->() const
    {
        return &(operator*());
    }

    self& operator++()
    {
        node = (link_type)((*node).next);
        return *this;
    }
    self operator++(int)
    {
        self tmp = *this;
        ++*this;
    }

    self operator--()
    {
        node = (link_type)((*node).prev);
        return *this;
    }

    self operator--(int)
    {
        self tmp = *this;
        --*this;
        return tmp;
    }
};
    

}
#endif