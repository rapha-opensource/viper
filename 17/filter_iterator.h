#include <functional>
#include <iterator>


template<class Iterator>

class FilterIterator : public Iterator {
    public:

    using predicate_t = std::function< bool (typename Iterator::reference) >;

    private:
    
    predicate_t _filter;
    const Iterator& _end;

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
        if( this != other ) {
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


