#include <array>
#include <type_traits>
#include <vector>

#include "catch.hpp"
#include "../iterator_cast.h"


using vi_t = std::vector<int>;
using vi_iter_t = vi_t::iterator;
using vi_filter_iter_t = FilterIterator<vi_iter_t>;

auto even = [](const int& i) { return i % 2 == 0; };


SCENARIO( "FilterIterator wrapping an iterator object", "[FilterIterator]" ) {

    GIVEN(" a specialization of FilterIterator ") {

        WHEN(" verifying basic Iterator concepts ") {

            THEN(" CopyConstructible ") {
                REQUIRE( std::is_copy_constructible<vi_filter_iter_t>::value );
            }

            THEN(" MoveAssignable ") {
                REQUIRE( std::is_move_assignable<vi_filter_iter_t>::value );
            }

            THEN(" CopyAssignable ") {
                REQUIRE( std::is_copy_assignable<vi_filter_iter_t>::value );
            }

            THEN(" Destructible ") {
                REQUIRE( std::is_destructible<vi_filter_iter_t>::value );
            }
        }
    }

    GIVEN( "A begin iterator of std::vector<int>{1,2,3,4} wrapped into a FilterIterator with an even filter" ) {

        vi_t vi = {1,2,3,4};
        auto it = vi_filter_iter_t(
                vi.begin(),
                vi.end(),
                even
                );

        WHEN( "dereferencing" ) {

            auto first_value = *it;

            THEN( "returns 2 " ) {
                REQUIRE( first_value == 2 );
            }
        }

        WHEN( "prefix incrementing the iterator" ) {
            ++it;

            THEN(" dereferencing returns 4 ") {
                REQUIRE( *it == 4 );
            }
        }

        WHEN( "postfix incrementing the iterator" ) {
            it++;

            THEN(" dereferencing returns 4 ") {
                REQUIRE( *it == 4 );
            }
        }

        WHEN( "dereferencing with postfix incrementing the iterator" ) {

            THEN(" dereferencing returns 4 ") {
                REQUIRE( *it++ == 2 );
                REQUIRE( *it == 4 );
            }
        }

        WHEN(" incrementing past the last one ") {
            ++it;
            ++it;

            THEN(" can compare to end iterator from original container") {
                REQUIRE( it == vi.end() );
            }
        }
    }

    GIVEN("a std::vector<int> = {1,2,3,4}") {

        vi_t vi = {1,2,3,4};

        WHEN(" building a FilterIterator with an l-value iterator and an l-value functor ") {
            auto vi_begin = vi.begin();
            auto vi_end = vi.end();
            int count = 0;
            auto fn = [&count](int& i) { ++count; return i % 2 == 1; };
            auto it = vi_filter_iter_t(vi_begin, vi_end, fn);

            THEN(" iterates through odd numbers ") {
                REQUIRE( *it == 1 );
                REQUIRE( *it++ == 1 );
                REQUIRE( *it == 3 );
            }
        }
    }

}

TEST_CASE(" FilterIterator specialization for pointer types ", " [FilterIterator], [pointer] ") {
    std::array<int, 4> some_ints = {1,2,3,4};

    FilterIterator<int*> it{ some_ints.begin(), some_ints.end(), even };
    
    REQUIRE( *it++ == 2 );
    REQUIRE( *it == 4 );
}


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

TEST_CASE(" 'in' function ", " [in] ") {

        vi_t vi = {1,2,3,4};
        int i = 4;

        REQUIRE( in(vi, i) ); // i is an l-value
        REQUIRE( in(vi, 2) ); // 2 is an r-value
        REQUIRE( in(vi, 3) );
        REQUIRE( in(vi, 4) );
        REQUIRE( in(vi_t{1,2,3,4}, 3) ); // vit_t{...} is an r-value

}