#ifndef __VIPER_RANGE__
#define __VIPER_RANGE__

#include <iterator>
#include <utility>


template <class T>

class RangeIterator {

    T _value;

    public:
        constexpr RangeIterator(const T value):_value(value) {}

        using difference_type = typename std::iterator_traits<T*>::difference_type;
        using value_type = typename std::iterator_traits<T*>::value_type;
        using pointer = typename std::iterator_traits<T*>::pointer;
        using reference = typename std::iterator_traits<T*>::reference;
        using iterator_category = typename std::iterator_traits<T*>::iterator_category;

        constexpr inline bool operator==(const RangeIterator& rhs) const {
            return _value == rhs._value;
        }

        constexpr inline bool operator!=(const RangeIterator& rhs) const {
            return _value != rhs._value;
        }

        constexpr inline difference_type operator-(const RangeIterator& rhs) const {
            return _value - rhs._value;
        }

        constexpr inline T operator*() const {
            return _value;
        }

        constexpr inline RangeIterator& operator++() {
            ++_value;
            return *this;
        }

        constexpr inline auto operator++(int) {
            auto iterator{*this};
            operator++();
            return iterator;
        }
        
};


template <class T>

class Range {

    RangeIterator<T> _start, _stop;

    public:
        constexpr Range(const T start, const T stop):_start(start), _stop(stop) {}

        constexpr inline RangeIterator<T> begin() const { return _start; }

        constexpr inline RangeIterator<T> end() const { return _stop; }

};


template<class T>
constexpr Range<T> range(const T& start, const T& stop) {
    return Range<T>(start, stop);
}

#endif 
