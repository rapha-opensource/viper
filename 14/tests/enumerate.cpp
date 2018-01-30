#include <array>
#include <forward_list>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <tuple>
#include <vector>

#include "catch.hpp"
#include "../enumerate.h"


TEST_CASE(" enumerate the contents of a container ", "[enumerate]") {

    std::vector<char> container {'a','b','c','d'};

    SECTION(" working with a std::pair of (index, character) directly ") {

        for( auto index_character : enumerate(container) ) {
            REQUIRE( index_character.first + 97 == index_character.second ); // 'a' is 97 in ASCII table
        }

    }

    SECTION(" using structural binding with std::tie ") {

        size_t index;
        char character;

        for( auto index_character : enumerate(container) ) {

            std::tie(index, character) = index_character;

            REQUIRE( index + 97 == character ); // 'a' is 97 in ASCII table
        }

    }

    // teaser: in the C++17 version you can simplify even further:
    // for( auto&& [index, character] : enumerate(container) { ... }
}


TEST_CASE(" enumerate a std::array ", "[enumerate] [array]") {

    std::array<int, 5> container {1,2,3,4,5};

    SECTION(" using std::pair ") {

        for( auto&& i_n: enumerate(container) ) {
            REQUIRE( i_n.first +1 == i_n.second );
        }
    }
}


TEST_CASE(" enumerate a std::deque ", "[enumerate] [deque]") {

    std::deque<int> container {1,2,3,4,5};

    SECTION(" using std::pair ") {

        for( auto&& i_n: enumerate(container) ) {
            REQUIRE( i_n.first +1 == i_n.second );
        }
    }
}


TEST_CASE(" enumerate a std::forward_list ", "[enumerate] [forward_list]") {

    std::forward_list<int> container {1,2,3,4,5};

    SECTION(" using std::pair ") {

        for( auto&& i_n: enumerate(container) ) {
            REQUIRE( i_n.first +1 == i_n.second );
        }
    }
}


TEST_CASE(" enumerate a std::list ", "[enumerate] [list]") {

    std::list<int> container {1,2,3,4,5};

    SECTION(" using std::pair ") {

        for( auto&& i_n: enumerate(container) ) {
            REQUIRE( i_n.first +1 == i_n.second );
        }
    }
}


TEST_CASE(" enumerate a std::set ", "[enumerate] [set]") {

    std::set<int> container {1,2,3,4,5};

    SECTION(" using std::pair ") {

        for( auto&& i_n: enumerate(container) ) {
            REQUIRE( i_n.first +1 == i_n.second );
        }
    }
}


TEST_CASE(" enumerate a std::map ", "[enumerate] [map]") {

    std::map<char, std::string> container {
        {'a', "alpha"},
        {'b', "bravo"},
        {'c', "charlie"},
        {'d', "delta"},
    };

    SECTION(" using std::pair ") {

        for( auto&& i_n: enumerate(container) ) {
            REQUIRE( i_n.first + 97 == i_n.second.first ); // 97 is 'a' in ASCII
        }
    }
}

// TODO multiset, multimap, unordered_set, unordered_map, unordered_multiset, unordered_multimap
