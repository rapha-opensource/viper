#include <vector>

#include "catch.hpp"
#include "../iterator_cast.h"


SCENARIO(" 'into' with only an input container, no transformation", "[into]") {

    GIVEN(" a std::vector<char> vc") {

        std::vector<char> vc{'a','b','c','d'};

        WHEN( " make a string using into<std::string>(vc) " ) {
            auto str = into<std::string>(vc);

            THEN(" the size and value match ") {
                REQUIRE( str.size() == vc.size() );
                REQUIRE( str == "abcd" );
            }

        }
    }
}

SCENARIO( " 'into' with a unary fn ", "[into], [transform]") {

    GIVEN(" a std::vector<int> ") {

        std::vector<int> vi{1,2,3,4};

        WHEN(" transformed 'into' in a string ") {
            auto str = into<std::string>([](const int& i) { return (char)(i+48); }, vi); 

            THEN(" must match in size and content ") {
                REQUIRE( str.size() == vi.size() );
                REQUIRE( str == "1234" );
            }
        }
    }
}


