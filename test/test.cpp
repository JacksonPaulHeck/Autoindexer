#include "catch.hpp"
#include "../src/JPVector.h"
#include "../src/JPString.h"

TEST_CASE("JPString Testing") {
    SECTION("JPString can be created from char*, JPString, and empty constructor; Equality operators") {
        auto *jpString = new JPString();
        REQUIRE(jpString->size() == 0);

        auto *jpString1 = new JPString("JPString");
        REQUIRE(jpString1->size() == 8);

        auto *jpString2 = new JPString(*jpString1);
        REQUIRE(jpString2->size() == 8);

        *jpString = *jpString2;

        REQUIRE(*jpString == "JPString");
        REQUIRE(*jpString1 == "JPString");
        REQUIRE(*jpString2 == "JPString");
        REQUIRE(*jpString == *jpString1);
        REQUIRE(*jpString2 == *jpString);
        REQUIRE(*jpString1 == *jpString2);

        delete jpString;
        delete jpString1;
        delete jpString2;
    }SECTION("JPString operator []") {
        auto *jpString3 = new JPString("JPString");
        try {
            REQUIRE(jpString3->operator[](0) == 'J');
            jpString3->operator[](100);
        } catch (exception &e) {
            REQUIRE(strcmp(e.what(), "Index is out of range for JPString!") == 0);
        }
        delete jpString3;
    }SECTION("JPString Substring function") {
        auto *jpString4 = new JPString("JPString");
        auto *jpString5 = new JPString();

        *jpString5 = jpString4->substring(1, 4);

        REQUIRE(*jpString5 == "PStr");

        try {
            *jpString5 = jpString4->substring(0, 100);
        }
        catch (exception &e) {
            REQUIRE(strcmp(e.what(), "Index is out of range for JPString!") == 0);
        }
        delete jpString4;
        delete jpString5;
    }SECTION("Assignment Operators") {
        auto *jpString6 = new JPString();
        auto *jpString7 = new JPString();

        jpString6->operator=("JPSTRING6");
        jpString7->operator=(*jpString6);

        REQUIRE(*jpString6 == "JPSTRING6");
        REQUIRE(*jpString7 == "JPSTRING6");

        delete jpString6;
        delete jpString7;
    }SECTION("Anti-Equality Operators") {
        auto *jpString8 = new JPString("JPSTRING8");
        auto *jpString9 = new JPString("JPSTRING9");

        REQUIRE(jpString8->operator!=('J'));
        REQUIRE(jpString9->operator!=(*jpString8));

        delete jpString8;
        delete jpString9;

    }SECTION("Additive Operators") {
//    JPString operator+=(const JPString &);
//    JPString operator+=(const char *);
//    JPString operator+=(int);
        auto *jpString10 = new JPString();
        auto *jpString11 = new JPString("JPSTRING11");
        int valueToBeAdded = 10;

        jpString10->operator+=(*jpString11);
        REQUIRE(*jpString10 == "JPSTRING11");

        jpString10->operator+=("JPSTRING10");
        REQUIRE(*jpString10 == "JPSTRING11JPSTRING10");

        jpString10->operator+=(valueToBeAdded);
        REQUIRE(*jpString10 == "JPSTRING11JPSTRING1010");

        delete jpString10;
        delete jpString11;
    }SECTION("Less than and Greater than Operators") {
        auto *jpString12 = new JPString("ABCD");
        auto *jpString13 = new JPString("EFGH");

        REQUIRE(*jpString12 < *jpString13);
        REQUIRE(*jpString13 > *jpString12);

        delete jpString12;
        delete jpString13;
    }SECTION("Size function") {
        //    int size() const;
        auto* jpString14 = new JPString("asdfghjklqwertyuiop");

        REQUIRE(jpString14->size() == 19);

        delete jpString14;
    }

    SECTION("Lowercase function") {
//    JPString & lowercase();
        auto* jpString15 = new JPString("JPStringThatIS234NOtCased..-+INAN//orMalFormat123./!");
        auto* jpString16 = new JPString();
        *jpString16 = jpString15->lowercase();

        REQUIRE(*jpString16 == "jpstringthatis234notcased..-+inan//ormalformat123./!");

        delete jpString15;
        delete jpString16;
    }


}

TEST_CASE("JPVector Testing") {
    auto *jpVector = new JPVector<int>();
    SECTION("Resize function changes size and capacity") {
        jpVector->push_back(1);
        jpVector->push_back(2);
        jpVector->push_back(3);
        jpVector->push_back(4);
        jpVector->push_back(5);
        jpVector->push_back(6);
        REQUIRE(jpVector->size() == 6);
        REQUIRE(jpVector->max_size() >= 6);
    }
    SECTION("Create JPVector from size constructor") {
        auto *jpVector1 = new JPVector<int>(5);
        REQUIRE(jpVector1->size() == 5);
        REQUIRE(jpVector1->max_size() >= 5);
        delete jpVector1;
    }
    SECTION("JPVector can throw exception for out of bounds") {
        auto *jpVector2 = new JPVector<char>();
        jpVector2->push_back('J');
        jpVector2->push_back('P');
        try {
            char y = jpVector2->operator[](100);
        } catch (exception &e) {
            REQUIRE(strcmp(e.what(), "Index is out of range for JPVector!") == 0);
        }
        delete jpVector2;
    }
    SECTION("JPVector can be created through copy constructor") {
        jpVector->push_back(0);
        jpVector->push_back(1);
        jpVector->push_back(2);
        jpVector->push_back(3);
        jpVector->push_back(4);
        jpVector->push_back(5);

        try {
            auto *jpVector3 = new JPVector<int>(*jpVector);
            REQUIRE(jpVector->at(0) == jpVector3->at(0));
            REQUIRE(jpVector->at(1) == jpVector3->at(1));
            REQUIRE(jpVector->at(2) == jpVector3->at(2));
            REQUIRE(jpVector->at(3) == jpVector3->at(3));
            REQUIRE(jpVector->at(4) == jpVector3->at(4));
            REQUIRE(jpVector->at(5) == jpVector3->at(5));
            delete jpVector3;
        } catch (exception &e) {
            REQUIRE(strcmp(e.what(), "Index is out of range for JPVector!") == 0);
        }
    }
    SECTION("JPVector assignment operator") {
        auto *jpVector4 = new JPVector<int>();
        auto *jpVector5 = new JPVector<int>();

        jpVector4->push_back(1);
        jpVector4->push_back(2);
        jpVector5->push_back(2);

        try {
            jpVector4->at(0) = jpVector5->at(0);
            jpVector4->at(1) = 3;
            REQUIRE(jpVector4->operator[](0) == 2);
            REQUIRE(jpVector4->operator[](1) == 3);
        } catch (exception &e) {
            REQUIRE(strcmp(e.what(), "Index is out of range for JPVector!") == 0);
        }
        delete jpVector4;
        delete jpVector5;
    }
    SECTION("JPVector push_back function") {
        auto *jpVector6 = new JPVector<int>();
        jpVector6->push_back(100);
        REQUIRE(jpVector6->size() == 1);
        REQUIRE(jpVector6->max_size() >= 1);
        try {
            REQUIRE(jpVector6->operator[](0) == 100);
        } catch (exception &e) {
            REQUIRE(strcmp(e.what(), "Index is out of range for JPVector!") == 0);
        }
        delete jpVector6;
    }
    SECTION("JPVector pop_back function") {
        auto *jpVector7 = new JPVector<int>();
        jpVector7->push_back(100);
        jpVector7->push_back(200);
        jpVector7->push_back(300);
        jpVector7->pop_back();

        REQUIRE(jpVector7->size() == 2);
        REQUIRE(jpVector7->max_size() >= 2);
        try {
            REQUIRE(jpVector7->operator[](1) == 200);
        } catch (exception &e) {
            REQUIRE(strcmp(e.what(), "Index is out of range for JPVector!") == 0);
        }
        delete jpVector7;
    }
    SECTION("JPVector operator[]") {
        auto *jpVector8 = new JPVector<int>();
        jpVector8->push_back(100);
        try {
            REQUIRE(jpVector8->operator[](0) == 100);
        } catch (exception &e) {
            REQUIRE(strcmp(e.what(), "Index is out of range for JPVector!") == 0);
        }
        delete jpVector8;
    }
    SECTION("JPVector at function") {
        auto *jpVector8 = new JPVector<int>();
        jpVector8->push_back(100);
        try {
            REQUIRE(jpVector8->at(0) == 100);
        } catch (exception &e) {
            REQUIRE(strcmp(e.what(), "Index is out of range for JPVector!") == 0);
        }
        delete jpVector8;
    }
    delete jpVector;
}
