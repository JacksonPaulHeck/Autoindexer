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

    delete jpString;
    delete jpString1;
    delete jpString2;
}

TEST_CASE("JPString can throw exception for out of bounds") {
    auto *jpString3 = new JPString("JPString");
    try {
        jpString3[100];
    } catch (exception &e) {
        cout << e.what();
    }
    delete jpString3;
}

TEST_CASE("JPVector can throw exception for out of bounds") {
    auto *jpVector1 = new JPVector<char>();
    jpVector1->push_back('J');
    jpVector1->push_back('P');
    try {
        jpVector1[100];
    } catch (exception &e) {
        cout << e.what();
    }
    delete jpVector1;
}

TEST_CASE("JPVector can be sized and resized", "[JPVector]") {
    auto *jpVector = new JPVector<int>(5);

    REQUIRE(jpVector->size() == 5);
    REQUIRE(jpVector->max_size() >= 5);

    SECTION("Resize function changes size and capacity") {
        jpVector->push_back(1);
        REQUIRE(jpVector->size() == 6);
        REQUIRE(jpVector->max_size() >= 6);
    }
    delete jpVector;
}
TEST_CASE("JPString Substring function"){
    auto* jpString4 = new JPString("JPString");
    auto* jpString5 = new JPString();

    *jpString5 = jpString4->substring(1, 4);

    REQUIRE(*jpString5 == "PStr");

    try{
        *jpString5 = jpString4->substring(0, 100);
    }
    catch(exception & e){
        cout << e.what();
    }
    delete jpString4;
    delete jpString5;
}