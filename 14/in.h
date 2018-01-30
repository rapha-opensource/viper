#include <algorithm>


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


