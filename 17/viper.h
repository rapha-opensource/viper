#include <functional>
#include <utility>
#include <iterator>
#include <algorithm>
#ifndef __VIPER_RANGE__
#define __VIPER_RANGE__



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


/*
 * This header provides an 'enumerate' function that behave similarly to Python's 'enumerate'.
 * For a given indexable container, it returns an iterator.
 * That iterator can be dereferenced into a pair of (index, value).
 *
 * For example:
 * std::vector<std::string> messages{"yo", "mama"};
 *
 * for(auto [index, message] : messages) {
 *      std::cout<< "[" << index << "] " << message << std::endl;
 * }
 *
 * Would print:
 * [0] yo
 * [1] mama
 */

template<class Indexable>
class Enumerate {

    const Indexable & data;

    public:
    Enumerate(const Indexable& container) noexcept :data(container) {}

    template<typename IterType>
    class Iterator {

        using type = std::remove_reference_t<Indexable>;
        using iterator_type = typename type::iterator;
        using reference = typename type::reference;
        using size_type = typename type::size_type;
        using value_type = typename type::value_type;

        IterType iter;
        size_type index;

        public:
            Iterator(const size_type& index, const IterType& iter): index(index), iter(iter) {}

            inline auto operator*() const {
                return std::make_pair(index, std::ref(*iter));
            }

            inline auto operator++() {
                ++index;
                ++iter;
                return *this;
            }

            inline auto operator!=(const Iterator<IterType>& rhs) const {
                return iter != rhs.iter;
            }

    };

    inline auto begin() { return Iterator<decltype(data.begin())>(0, data.begin()); }

    inline auto end() { return Iterator<decltype(data.end())>(std::distance(data.begin(), data.end()), data.end()); }

};


template<class Indexable>
inline auto enumerate(Indexable&& container) noexcept {
    return Enumerate<decltype(container)>(std::forward<Indexable>(container));
}



template<class Container>
constexpr bool in(const Container& c, typename Container::const_reference value) {
    return std::find(c.cbegin(), c.cend(), value) != c.cend();
}

template<class Container>
constexpr bool in(const Container& c, typename Container::value_type&& value) {
    return std::find(c.cbegin(), c.cend(), value) != c.cend();
}

template<class Container>
constexpr bool in(Container&& c, typename Container::value_type&& value) {
    return std::find(c.cbegin(), c.cend(), value) != c.cend();
}


#ifndef __VIPER_GRID__
#define __VIPER_GRID__




template<std::size_t column_number, std::size_t rows, std::size_t cols, class SequenceContainer>
class ColumnDimension {

    protected:

    const SequenceContainer& data;

    public:

    template<typename iterator>
    class ColumnIterator {

        public:

            using difference_type = typename std::iterator_traits<iterator>::difference_type;
            using value_type = typename std::iterator_traits<iterator>::value_type;
            using pointer = typename std::iterator_traits<iterator>::pointer;
            using reference = typename std::iterator_traits<iterator>::reference;
            using const_reference = typename std::iterator_traits<iterator>::reference;
            using iterator_category = typename std::iterator_traits<iterator>::iterator_category;

        protected:

            iterator _iter;

        public:

            ColumnIterator(const iterator& iter): _iter(iter) {}

            inline typename std::conditional<std::is_const<iterator>::value, const_reference, reference>::type operator*() const {
                return *_iter;
            }

            inline auto operator!=(const ColumnIterator<iterator>& rhs) const {
                return _iter != rhs._iter;
            }

            inline auto operator++() {
                std::advance(_iter, cols);
                return *this;
            }

    };

    using container_t = std::remove_reference_t<SequenceContainer>;
    using value_type = typename container_t::value_type;
    using size_type = typename container_t::size_type;
    using difference_type = typename container_t::difference_type;
    using reference = typename container_t::reference;
    using const_reference = typename container_t::const_reference;
    using pointer = typename container_t::pointer;
    using const_pointer = typename container_t::const_pointer;
    using iterator = ColumnIterator<typename container_t::iterator>;
    using const_iterator = ColumnIterator<typename container_t::const_iterator>;

    constexpr ColumnDimension(const SequenceContainer& container)
        :data(container) {}

    //
    // READ OPS
    //

    constexpr size_type size() const noexcept {
        return rows;
    }

    constexpr const_reference operator[]( size_type pos ) const {
        return data[ column_number + pos*cols ];
    }

    //
    // WRITE OPS
    //

    constexpr reference operator[]( size_type pos ) {
        return data[ column_number + pos*cols ];
    }

    constexpr iterator begin() { return iterator(std::next(data.begin(), column_number)); }

    constexpr iterator end() { return iterator(std::next(data.begin(), column_number + rows*cols)); }

    constexpr const_iterator cbegin() const { return const_iterator(std::next(data.cbegin(), column_number)); }

    constexpr const_iterator cend() const { return const_iterator(std::next(data.cbegin(), column_number + rows*cols)); }

};


template<std::size_t row_number, std::size_t rows, std::size_t cols, class SequenceContainer>
class RowDimension {

    protected:

        const SequenceContainer& data;

    public:

        template<typename iterator>
            class RowIterator {

                public:

                    using difference_type = typename std::iterator_traits<iterator>::difference_type;
                    using value_type = typename std::iterator_traits<iterator>::value_type;
                    using pointer = typename std::iterator_traits<iterator>::pointer;
                    using reference = typename std::iterator_traits<iterator>::reference;
                    using const_reference = typename std::iterator_traits<iterator>::reference;
                    using iterator_category = typename std::iterator_traits<iterator>::iterator_category;

                protected:

                    iterator _iter;

                public:

                    RowIterator(const iterator& iter): _iter(iter) {}

                    inline typename std::conditional<std::is_const<iterator>::value, const_reference, reference>::type operator*() const {
                        return *_iter;
                    }

                    inline auto operator!=(const RowIterator<iterator>& rhs) const {
                        return _iter != rhs._iter;
                    }

                    inline auto operator++() {
                        _iter++;
                        return *this;
                    }

            };

        using container_t = std::remove_reference_t<SequenceContainer>;
        using value_type = typename container_t::value_type;
        using size_type = typename container_t::size_type;
        using difference_type = typename container_t::difference_type;
        using reference = typename container_t::reference;
        using const_reference = typename container_t::const_reference;
        using pointer = typename container_t::pointer;
        using const_pointer = typename container_t::const_pointer;
        using iterator = RowIterator<typename container_t::iterator>;
        using const_iterator = RowIterator<typename container_t::const_iterator>;

        constexpr RowDimension(const SequenceContainer& container)
            :data(container) {}

        //
        // READ OPS
        //

        constexpr size_type size() const noexcept {
            return cols;
        }

        constexpr const_reference operator[]( size_type pos ) const {
            return data[ row_number*cols + pos ];
        }

        constexpr const_iterator cbegin() const { return const_iterator(std::next(data.cbegin(), row_number*cols)); }

        constexpr const_iterator cend() const { return const_iterator(std::next(data.cbegin(), row_number*cols + cols)); }

        //
        // WRITE OPS
        //

        constexpr reference operator[]( size_type pos ) {
            return data[ row_number*cols + pos ];
        }

        constexpr iterator begin() { return iterator(std::next(data.begin(), row_number*cols)); }

        constexpr iterator end() { return iterator(std::next(data.begin(), row_number*cols + cols)); }
};


template<std::size_t column_number, std::size_t rows, std::size_t cols, class SequenceContainer>
inline auto col(SequenceContainer&& container) {
    return ColumnDimension<
        column_number,
        rows,
        cols,
        SequenceContainer
            > (std::forward<SequenceContainer>(container));
}


template<std::size_t row_number, std::size_t rows, std::size_t cols, class SequenceContainer>
inline auto row(SequenceContainer&& container) {
    return RowDimension<
        row_number,
        rows,
        cols,
        SequenceContainer
            > (std::forward<SequenceContainer>(container));
}


#endif


template<class Iterator>

class FilterIterator : public Iterator {
    public:

    using predicate_t = std::function< bool (typename Iterator::reference) >;

    private:
    
    predicate_t _filter;
    Iterator _end;

    inline void move_to_next_valid_value() {
        while( (*this!=_end) && !_filter(**this)) Iterator::operator++();
    }


    public:

    FilterIterator(const FilterIterator& iter):FilterIterator(iter, iter._end, iter._filter) {}

    FilterIterator(const Iterator& begin, const Iterator& end, const predicate_t& filter)
        : Iterator(begin),_filter(filter),_end(end) {
            move_to_next_valid_value();
        }

    FilterIterator(Iterator&& begin, Iterator&& end, predicate_t&& filter)
        : Iterator(std::move(begin)), _filter(std::move(filter)), _end(std::move(end)) {
            move_to_next_valid_value();
        }

    FilterIterator& operator=(const FilterIterator& other) {
        if( this != &other ) {
            _filter = other._filter;
            _end = other._end;
        }
        return *this;
    }

    FilterIterator& operator=(FilterIterator&& other) {
        if( this != &other ) {
            _filter = std::move(other._filter);
            _end = std::move(other._end);
        }
        return *this;
    }

    inline FilterIterator& operator++() {
        do {
            Iterator::operator++();
        } while( (*this!=_end) && !_filter(**this) );
        return *this;
    }

    inline auto operator++(int) {
        auto iterator{*this};
        operator++();
        return iterator;
    }
};


template<class T>

class FilterIterator<T*> {

    public:

    using predicate_t = typename std::function< bool (const T&) >;

    private:

    const T *_iter, *_end;
    const predicate_t& _filter;

    inline void move_to_next_valid_value() {
        while( (*this!=_end) && !_filter(**this)) ++_iter;
    }

    public:

        using difference_type = typename std::iterator_traits<T*>::difference_type;
        using value_type = typename std::iterator_traits<T*>::value_type;
        using pointer = typename std::iterator_traits<T*>::pointer;
        using reference = typename std::iterator_traits<T*>::reference;
        using iterator_category = typename std::iterator_traits<T*>::iterator_category;

        FilterIterator(const T* begin, const T* end, const predicate_t& filter)
            : _iter(begin), _end(end), _filter(filter) {
                move_to_next_valid_value();
            }

        inline bool operator==(const T* rhs) const {
            return _iter == rhs;
        }

        inline bool operator==(const FilterIterator<T*>& rhs) const {
            return _iter == rhs._iter;
        }

        inline bool operator!=(const T* rhs) const {
            return _iter != rhs;
        }

        inline bool operator!=(const FilterIterator<T*>& rhs) const {
            return _iter != rhs._iter;
        }

        inline difference_type operator-(const T* rhs) const {
            return _iter - rhs;
        }

        inline difference_type operator-(const FilterIterator<T*>& rhs) const {
            return _iter - rhs._iter;
        }

        inline const T& operator*() const {
            return *_iter;
        }

        inline FilterIterator& operator++() {
            do {
                ++_iter;
            } while( (*this!=_end) && !_filter(**this) );
            return *this;
        }

        inline auto operator++(int) {
            auto iterator{*this};
            operator++();
            return iterator;
        }
};




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
    return T(c.begin(), c.end());
}


template<class T, class UnaryFunction, class Container>
T into(const UnaryFunction& fn, Container&& c) {
    return T(iterator_cast(c.cbegin(), fn), iterator_cast(c.cend(), fn));
}




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


