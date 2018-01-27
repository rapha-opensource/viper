#include <tuple>
#include <vector>

#include "catch.hpp"
#include "../enumerate.h"


TEST_CASE(" enumerate the contents of a container ", "[enumerate]") {

    std::vector<char> vc = {'a','b','c','d'};

    SECTION(" working with a std::pair of (index, character) directly ") {

        for( auto index_character : enumerate(vc) ) {
            REQUIRE( index_character.first + 97 == index_character.second ); // 'a' is 97 in ASCII table
        }

    }

    SECTION(" using structural binding with std::tie ") {

        size_t index;
        char character;

        for( auto index_character : enumerate(vc) ) {

            std::tie(index, character) = index_character;

            REQUIRE( index + 97 == character ); // 'a' is 97 in ASCII table
        }

    }

    // teaser: in the C++17 version you can simplify even further:
    // for( auto&& [index, character] : enumerate(vc) { ... }
}

