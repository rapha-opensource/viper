#include <iterator>
#include <functional>
#include <utility>


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

