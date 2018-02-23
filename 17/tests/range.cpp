#include <vector>

#include "catch.hpp"

#include "../headers/range.h"
#include "../headers/iterator_cast.h"


constexpr unsigned int sum_1_10() {
    auto _1_through_10 = range(1,11);
    unsigned int ret = 0;
    for( auto i : range(1,11) ) {
        ret += i;
    }
    return ret;
}

template <unsigned int N> unsigned int sumN() { return N; }


TEST_CASE(" 'range' function ", " [range] ") {

    SECTION(" into ") {
        auto vi = into<std::vector<int>>(range(1,5));

        REQUIRE( vi == decltype(vi){1,2,3,4} );
    }


    SECTION(" range-for ") {

        int k {1};

        for( auto&& i : range(1,5) ) {
            REQUIRE( i == k++ );
        }

    }

    SECTION(" constexpr range ") {
        REQUIRE( sumN<sum_1_10()>() == 55 );
    }

}
