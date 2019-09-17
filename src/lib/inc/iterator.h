#ifndef _TINYSTL_ITERATOR_H_
#define _TINYSTL_ITERATOR_H_

namespace tinystl
{
    struct InputIteratorTag{};
    struct OutputIteratorTag{};
    struct ForwardIteratorTag : public InputIteratorTag{};
    struct BidirectionalIteratorTag : public ForwardIteratorTag{};
    struct RandomAccessIteratorTag : public BidirectionalIteratorTag{};

    


}

#endif