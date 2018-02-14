#include <vector>

#include "catch.hpp"
#include "../headers/range.h"
#include "../headers/iterator_cast.h"


TEST_CASE(" 'range' function ", " [range] ") {

    SECTION(" into ", "[into]") {
        auto vi = into<std::vector<int>>(range(1,5));

        REQUIRE( vi == decltype(vi){1,2,3,4} );
    }


    SECTION(" range-for ", "[range-for]") {

        int k {1};

        for( auto&& i : range(1,5) ) {
            REQUIRE( i == k++ );
        }

    }
}
