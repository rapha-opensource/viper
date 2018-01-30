#include <array>
#include <vector>

#include "catch.hpp"
#include "../headers/filter.h"


using vi_t = std::vector<int>;
using vi_iter_t = vi_t::iterator;
using vi_filter_iter_t = FilterIterator<vi_iter_t>;

auto even = [](const int& i) { return i % 2 == 0; };


SCENARIO(" filter function ", " [filter] ") {

    GIVEN("a std::vector<int> vi = {1,2,3,4}") {

        vi_t vi = {1,2,3,4};

        WHEN(" std::vector<int> filtered = filter(even, vi); " ) {

            auto even = [](int i) { return i % 2 == 0; };
            std::vector<int> filtered = filter(even, vi);

            THEN(" filtered contains only even numbers ") {
                REQUIRE( filtered == std::vector<int>{2,4} );
            }
        }
    }

}
