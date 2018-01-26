#include <array>
#include <iostream>
#include <vector>

#include "catch.hpp"
#include "../iterator_cast.h"


SCENARIO( "iterator_cast wrapping an iterator object", "[iterator_cast], [object]" ) {

    GIVEN( "A vector of integers [1,2,3,4]" ) {
        std::vector<int> vi{1,2,3,4};

        WHEN( "mapped into a string" ) {
            const auto convert = [](const int& i) { return (std::string::value_type)(i+48); };
            auto str = std::string(iterator_cast(vi.cbegin(), convert), iterator_cast(vi.cend(), convert));

            THEN( "returns '1234' " ) {
                REQUIRE( str == "1234" );
            }
        }
    }
}

SCENARIO( "iterator_cast wrapping a pointer", "[iterator_cast], [pointer]" ) {

    GIVEN( "An std::array of bools" ) {
        std::array<bool, 10> ab{true, false, true, false, true, false, true, false, true, false};

        WHEN( " making 2 iterators returning a char " ) {
            const auto bool_to_char = [](const bool& b) { return (std::string::value_type)(b?'0':'1'); };
            auto begin = iterator_cast(ab.cbegin(), bool_to_char);
            auto end = iterator_cast(ab.cend(), bool_to_char);
            std::string str(begin, end);

            THEN( "the iterators work" ) {
                REQUIRE( begin != end );
                REQUIRE( (end - begin) == std::distance(ab.cbegin(), ab.cend()) );
                REQUIRE( str == "0101010101" );
            }
        }
    }
}

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


