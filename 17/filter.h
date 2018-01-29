#include "iterator_cast.h"


template<class ContainerOut, class ContainerIn>
ContainerOut filter(const typename FilterIterator<typename ContainerIn::const_iterator>::predicate_t& fn, const ContainerIn& in) {
    using filter_type_t = FilterIterator<typename ContainerIn::const_iterator>;
    ContainerOut out{
        filter_type_t(
                in.cbegin(),
                in.cend(),
                fn
                ),
        filter_type_t(
                in.cend(),
                in.cend(),
                fn
                ),
    };
    return out;
}


template<class ContainerIn>
ContainerIn filter(const typename FilterIterator<typename ContainerIn::const_iterator>::predicate_t& fn, const ContainerIn& in) {
    using filter_type_t = FilterIterator<typename ContainerIn::const_iterator>;
    ContainerIn out{
        filter_type_t(
                in.cbegin(),
                in.cend(),
                fn
                ),
        filter_type_t(
                in.cend(),
                in.cend(),
                fn
                ),
    };
    return out;
}


