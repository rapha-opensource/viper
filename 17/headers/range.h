#include <iterator>
#include <utility>


template <class T>

class RangeIterator {

    T _value;

    public:
        RangeIterator(const T value):_value(value) {}

        using difference_type = typename std::iterator_traits<T*>::difference_type;
        using value_type = typename std::iterator_traits<T*>::value_type;
        using pointer = typename std::iterator_traits<T*>::pointer;
        using reference = typename std::iterator_traits<T*>::reference;
        using iterator_category = typename std::iterator_traits<T*>::iterator_category;

        inline bool operator==(const RangeIterator& rhs) const {
            return _value == rhs._value;
        }

        inline bool operator!=(const RangeIterator& rhs) const {
            return _value != rhs._value;
        }

        inline difference_type operator-(const RangeIterator& rhs) const {
            return _value - rhs._value;
        }

        inline T operator*() const {
            return _value;
        }

        inline RangeIterator& operator++() {
            ++_value;
            return *this;
        }

        inline auto operator++(int) {
            auto iterator{*this};
            operator++();
            return iterator;
        }
        
};


template <class T>

class Range {

    RangeIterator<T> _start, _stop;

    public:
        Range(const T start, const T stop):_start(start), _stop(stop) {}

        inline RangeIterator<T> begin() const { return _start; }

        inline RangeIterator<T> end() const { return _stop; }

};


template<class T>
Range<T> range(const T& start, const T& stop) {
    return Range<T>(start, stop);
}

//Iterable<class T, class Distance> range(const T& start, const T& stop, const Distance& step) {
//}

 
