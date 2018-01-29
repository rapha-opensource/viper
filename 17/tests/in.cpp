#include <vector>

#include "catch.hpp"
#include "../in.h"


TEST_CASE(" 'in' function ", " [in] ") {

    std::vector<int> vi = {1,2,3,4};
    int i = 4;

    REQUIRE( in(vi, i) ); // i is an l-value
    REQUIRE( in(vi, 2) ); // 2 is an r-value
    REQUIRE( in(vi, 3) );
    REQUIRE( in(vi, 4) );
    REQUIRE( in(std::vector<int>{1,2,3,4}, 3) ); // std::vector<int>{...} is an r-value

}
