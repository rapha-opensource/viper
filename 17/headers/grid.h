#ifndef __VIPER_GRID__
#define __VIPER_GRID__


#include <iterator>


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
