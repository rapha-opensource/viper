#include <iterator>


template<class Iterator, class UnaryFunction>

class Iter : public Iterator {
    
    UnaryFunction& _convert;

    public:

    //TODO provide valid value_type and reference!
        //using value_type = typename std::iterator_traits<T*>::value_type;
        //using reference = typename std::iterator_traits<T*>::reference;

        Iter(const Iterator& iter, const UnaryFunction& convert)
            : Iterator(iter),_convert(convert) {}

        Iter(Iterator&& iter, UnaryFunction&& convert)
            : Iterator(std::move(iter)), _convert(std::move(convert)) {}

        inline auto operator*() {
            return _convert(Iterator::operator*());
        }
};


template<class T, class UnaryFunction>

class Iter<T*, UnaryFunction> {
    T* _iter;
    UnaryFunction& _convert;

    public:

        using difference_type = typename std::iterator_traits<T*>::difference_type;
        using value_type = typename std::iterator_traits<T*>::value_type;
        using pointer = typename std::iterator_traits<T*>::pointer;
        using reference = typename std::iterator_traits<T*>::reference;
        using iterator_category = typename std::iterator_traits<T*>::iterator_category;

        Iter(T* iter, const UnaryFunction& convert)
            : _iter(iter),_convert(convert) {}

        //Iter(T* iter, UnaryFunction&& convert)
            //: _iter(iter),_convert(std::move(convert)) {}

        inline bool operator!=(const Iter<T*, UnaryFunction>& rhs) const {
            return _iter != rhs._iter;
        }

        inline auto operator++() {
            ++_iter;
            return *this;
        }

        inline auto operator*() {
            return _convert(*_iter);
        }
};


template<class T, class UnaryFunction>

class Iter<const T*, UnaryFunction> {
    const T* _iter;
    UnaryFunction& _convert;

    public:

        using difference_type = typename std::iterator_traits<const T*>::difference_type;
        using value_type = typename std::iterator_traits<const T*>::value_type;
        using pointer = typename std::iterator_traits<const T*>::pointer;
        using reference = typename std::iterator_traits<const T*>::reference;
        using iterator_category = typename std::iterator_traits<const T*>::iterator_category;

        Iter(const T* iter, const UnaryFunction& convert)
            : _iter(iter),_convert(convert) {}

        //Iter(T* iter, UnaryFunction&& convert)
            //: _iter(iter),_convert(std::move(convert)) {}

        inline bool operator!=(const Iter<const T*, UnaryFunction>& rhs) const {
            return _iter != rhs._iter;
        }

        inline difference_type operator-(const Iter<const T*, UnaryFunction>& rhs) const {
            return _iter - rhs._iter;
        }

        inline auto operator++() {
            ++_iter;
            return *this;
        }

        inline auto operator*() {
            return _convert(*_iter);
        }
};


template<class Iterator, class UnaryFunction>
inline auto iterator_cast(Iterator&& iter, UnaryFunction&& convert) {
    return Iter<Iterator, UnaryFunction>(std::forward<Iterator>(iter), std::forward<UnaryFunction>(convert));
};


template<class T, class UnaryFunction>
inline auto iterator_cast(T* iter, UnaryFunction&& convert) {
   return Iter<decltype(iter), decltype(convert)>(iter, std::forward<UnaryFunction>(convert));
}


template<class T, class UnaryFunction>
inline auto iterator_cast(const T* iter, UnaryFunction&& convert) {
   return Iter<decltype(iter), decltype(convert)>(iter, std::forward<UnaryFunction>(convert));
}


template<class T, class Container>
T into(const Container& c) {
    return T(c.cbegin(), c.cend());
}


template<class T, class UnaryFunction, class Container>
T into(const UnaryFunction& fn, Container&& c) {
    return T(iterator_cast(c.cbegin(), fn), iterator_cast(c.cend(), fn));
}


