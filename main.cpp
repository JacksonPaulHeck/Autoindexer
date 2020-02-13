#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <iostream>
#include <fstream>
#include "JPString.h"
#include "JPVector.h"

using namespace std;

int main() {
    cout << "JPString and JPVector" << endl;

    JPVector<JPString> jpVector;
    JPString jpString;

    jpString = "JPString";

    jpVector.push_back(jpString);

    cout << jpVector[0];

    int result = Catch::Session().run();

    return 0;
}
