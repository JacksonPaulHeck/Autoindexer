#include <iostream>
#include <fstream>
#include "JPString.h"
#include <string>
#include "JPVector.h"

using namespace std;

int main() {
//    JPString jpString("JPString");
//    JPString jpString1("JPString1");
//    JPString jpString2("JPString2");
//
//    cout << jpString << endl;
//    cout << jpString2 << endl;
//    cout << jpString1 << endl;
//
//    JPString* pJPString = new JPString(jpString);
//    JPString* pJPString1 = new JPString(*pJPString);
//    JPString* cpJPString = new JPString("cpJPString");
//
//    *cpJPString = *pJPString;
//
//    *pJPString = jpString1;
//
//    *pJPString1 = *pJPString;
//
//    cout << *pJPString << endl;
//    cout << *pJPString1 << endl;
//
//
//    delete pJPString;
//    delete pJPString1;
//    delete cpJPString;

    JPVector<int>* jpVector = new JPVector<int>(4);

    delete jpVector;

    return 0;
}
