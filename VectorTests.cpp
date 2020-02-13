#include "catch.hpp"
#include "JPVector.h"




TEST_CASE("JPVector can be sized and resized", "[JPVector]"){
    JPVector<int>* jpVector = new JPVector<int>(5);

    REQUIRE(jpVector->size() == 5);
    REQUIRE(jpVector->max_size() >= 5);

    SECTION("Resize function changes size and capacity"){
        jpVector->push_back(1);
        REQUIRE(jpVector->size() == 6);
        REQUIRE(jpVector->max_size() >= 6);
    }
}