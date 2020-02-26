#include "catch.hpp"
#include "JPVector.h"
#include "JPString.h"


TEST_CASE("JPString can be assigned based off of char* and JPString"){
    auto* jpString = new JPString();
    *jpString = "JPString";
    auto* jpString1 = new JPString("JPString");
    auto* jpString2 = new JPString(*jpString);

    REQUIRE(*jpString == "JPString");
    REQUIRE(*jpString1 == "JPString");
    REQUIRE(*jpString2 == "JPString");

    REQUIRE(*jpString == *jpString1);
    REQUIRE(*jpString2 == *jpString);
    REQUIRE(*jpString1 == *jpString2);

    try{
        cout << jpString[100] << endl;
    }catch(exception& e){
        cout << e.what() << endl;
    }

    delete jpString;
    delete jpString1;
    delete jpString2;
}

TEST_CASE("JPVector can be sized and resized", "[JPVector]"){
    auto* jpVector = new JPVector<int>(5);

    REQUIRE(jpVector->size() == 5);
    REQUIRE(jpVector->max_size() >= 5);

    SECTION("Resize function changes size and capacity"){
        jpVector->push_back(1);
        REQUIRE(jpVector->size() == 6);
        REQUIRE(jpVector->max_size() >= 6);
    }
    delete jpVector;
}
