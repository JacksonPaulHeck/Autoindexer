#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <iostream>
#include "JPString.h"
#include "JPVector.h"
#include "Driver.h"

using namespace std;

int main(int argc, char **argv) {
    //if no arguments, run the catch tests
    if (argc == 1) {
        Catch::Session().run();
        return 0;
    }

    ifstream inFile(argv[1]);  //the input file
    ifstream bookIn(argv[2]);  //the book file
    ofstream outFile(argv[3]); //the output file

    //check if all three files are open
    if (inFile.is_open() && bookIn.is_open() && outFile.is_open()) {
        cout << "Its Open" << endl;
    }

    //create the input vector
    JPVector<JPString *> inputJPVector;

    //populate the input vector from the input file
    populateJPVectorFromInput(inputJPVector, inFile);

    //parse through each of the inputs from the input file and pass to the phrase determining program
    for (int i = 0; i < inputJPVector.size(); i++) {
        if (!isPhrase(*inputJPVector.at(i))) {
            //if the input is a single word, run the word function
            parseThroughTheBookWithWord(*inputJPVector.at(i), bookIn);
        } else {
            //if the input is a phrase, run the phrase function
            parseThroughTheBookWithPhrase(*inputJPVector.at(i), bookIn);
        }
    }

    //print the nexly changed input vector elements to the output file
    printToFile(inputJPVector, outFile);

    //delete each of the elements in the input vector
    for (int i = 0; i < inputJPVector.size(); i++) {
        delete inputJPVector.at(i);
    }

    //close each of the files
    inFile.close();
    bookIn.close();
    outFile.close();

    return 0;
}                               //main driver function

