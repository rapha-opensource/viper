#include <array>
#include <type_traits>

#include "catch.hpp"

#include "../headers/enumerate.h"
#include "../headers/grid.h"
#include "../headers/iterator_cast.h"


TEST_CASE(" grid ", "[grid]") {

    const unsigned int rows{2}, cols{3};

    std::array<int, rows*cols> rectangle { 0, 1, 2, 3, 4, 5 };

    SECTION(" col ") {

        size_t i=0;
        auto col_0 = col<0, rows, cols>(rectangle);

        REQUIRE( std::is_same<decltype(*col_0.cbegin()), decltype(*rectangle.cbegin())>::value );
        REQUIRE( std::is_same<decltype(*col_0.cend()), decltype(*rectangle.cend())>::value );
        REQUIRE( std::is_same<decltype(*col_0.begin()), decltype(*rectangle.begin())>::value );
        REQUIRE( std::is_same<decltype(*col_0.end()), decltype(*rectangle.end())>::value );

        REQUIRE( std::is_same<decltype(col_0)::container_t, decltype(rectangle)>::value );
        REQUIRE( std::is_same<decltype(col_0)::value_type, decltype(rectangle)::value_type>::value );
        REQUIRE( std::is_same<decltype(col_0)::iterator, decltype(col_0.begin())>::value );
        REQUIRE( std::is_same<decltype(col_0)::const_iterator, decltype(col_0.cbegin())>::value );
        
        REQUIRE( col_0.size() == 2 );
        
        REQUIRE( col_0.begin() != col_0.end() );

        auto it = col_0.begin();

        REQUIRE( *it == 0 );

        //
        // READ
        //

        REQUIRE( col_0[0] == 0 );
        REQUIRE( col_0[1] == 3 );
        for( const auto& element : col_0 ) {

            REQUIRE( element == rectangle[i] );

            i += cols;

        }

        auto col_2 = col<2, rows, cols>(rectangle);

        REQUIRE( col_2[0] == 2 );
        REQUIRE( col_2[1] == 5 );

        int j = 2;
        for( const auto& element : col_2 ) {

            REQUIRE( element == rectangle[j] );

            j += cols;

        }

        //
        // WRITE
        //
        for( auto&& element : col_0 ) { element += 7; }

        REQUIRE( rectangle == std::array<int, rows*cols>{ 7, 1, 2, 10, 4, 5 } );

        col_0[0] = 33;
        REQUIRE( col_0[0] == 33 );
        
    }


    SECTION(" row ") {

        // std::array<int, rows*cols> rectangle { 0, 1, 2, 3, 4, 5 };
        auto row_1 = row<1, rows, cols>(rectangle);

        int i=3;
        for( auto&& element : row_1 ) {
            REQUIRE( element == rectangle[i++] );
        }

        REQUIRE( row_1[0] == 3 );
        REQUIRE( row_1[1] == 4 );
        REQUIRE( row_1[2] == 5 );

    }

}
