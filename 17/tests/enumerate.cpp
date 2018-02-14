#include <array>
#include <forward_list>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "catch.hpp"
#include "../headers/enumerate.h"


TEST_CASE(" enumerate the contents of a container ", "[enumerate]") {

    std::vector<char> vc {'a','b','c','d'};

    for( auto&& [index, value] : enumerate(vc) ) {
        REQUIRE( index + 97 == value ); // 'a' is 97 in ASCII table
    }
}


TEST_CASE(" writable content ", "[write]") {
    std::vector<int> vi{1,2,3,4}, vo{2,4,6,8};

    for( auto&& [index, value] : enumerate(vi) ) {
        value *= 2;
    }

    REQUIRE( vi == vo );
}


TEST_CASE(" enumerate a std::array ", "[enumerate] [array]") {

    std::array<int, 5> ai {1,2,3,4,5};

    SECTION(" using std::pair ") {

        for( auto&& [index, value] : enumerate(ai) ) {
            REQUIRE( index +1 == value );
        }
    }
}


TEST_CASE(" enumerate a std::deque ", "[enumerate] [deque]") {

    std::deque<int> container {1,2,3,4,5};

    SECTION(" using std::pair ") {

        for( auto&& [index, value] : enumerate(container) ) {
            REQUIRE( index +1 == value );
        }
    }
}


TEST_CASE(" enumerate a std::forward_list ", "[enumerate] [forward_list]") {

    std::forward_list<int> container {1,2,3,4,5};

    SECTION(" using std::pair ") {

        for( auto&& [index, value] : enumerate(container) ) {
            REQUIRE( index +1 == value );
        }
    }
}


TEST_CASE(" enumerate a std::list ", "[enumerate] [list]") {

    std::list<int> container {1,2,3,4,5};

    SECTION(" using std::pair ") {

        for( auto&& [index, value] : enumerate(container) ) {
            REQUIRE( index +1 == value );
        }
    }
}


TEST_CASE(" enumerate a std::set ", "[enumerate] [set]") {

    std::set<int> container {1,2,3,4,5};

    SECTION(" using std::pair ") {

        for( auto&& [index, value] : enumerate(container) ) {
            REQUIRE( index +1 == value );
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

        for( auto&& [index, value] : enumerate(container) ) {
            REQUIRE( index + 97 == value.first ); // 97 is 'a' in ASCII
        }
    }
}

// TODO multiset, multimap, unordered_set, unordered_map, unordered_multiset, unordered_multimap

