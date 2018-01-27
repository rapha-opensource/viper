#include <vector>

#include "catch.hpp"
#include "../enumerate.h"


TEST_CASE(" 'into' with only an input container, no transformation", "[into]") {

    std::vector<char> vc = {'a','b','c','d'};

    for( auto index_value : enumerate(vc) ) {
        REQUIRE( index_value.first + 97 == index_value.second ); // 'a' is 97 in ASCII table
    }
}

