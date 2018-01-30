#include <vector>

#include "catch.hpp"
#include "../viper.h"


TEST_CASE(" make sure merged header has all the interfaces ", " [merged] ") {

    std::vector<int> container = {1,2,3,4};

    SECTION(" in ") {

        int i = 4;

        REQUIRE( in(container, i) ); // i is an l-value
        REQUIRE( in(container, 3) ); // i is an r-value

    }

    SECTION(" enumerate ") {
        for( auto&& i_n: enumerate(container) ) {
            REQUIRE( i_n.first +1 == i_n.second );
        }
    }

    SECTION(" filter ") {
        auto even = [](int i) { return i % 2 == 0; };
        std::vector<int> filtered = filter(even, container);

        REQUIRE( filtered == std::vector<int>{2,4} );
    }

    SECTION(" into ") {
        auto str = into<std::string>([](const int& i) { return (char)(i+48); }, container); 

        REQUIRE( str.size() == container.size() );
        REQUIRE( str == "1234" );
    }

}
