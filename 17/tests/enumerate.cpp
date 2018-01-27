#include <vector>

#include "catch.hpp"
#include "../enumerate.h"


TEST_CASE(" enumerate the contents of a container ", "[enumerate]") {

    std::vector<char> vc = {'a','b','c','d'};

    for( auto&& [index, value] : enumerate(vc) ) {
        REQUIRE( index + 97 == value ); // 'a' is 97 in ASCII table
    }
}

