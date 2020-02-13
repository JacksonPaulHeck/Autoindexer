#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <iostream>
#include <fstream>
#include "JPString.h"
#include "JPVector.h"

using namespace std;

void parseThroughTheBook(JPVector<JPString*>&, ifstream&, ofstream&);
void populateJPVectorFromInput(JPVector<JPString*>&, ifstream&);

int main(int argc, char** argv) {
    int result = Catch::Session().run();

    ifstream inFile(argv[1]);
    ifstream bookIn(argv[2]);
    ofstream outFile(argv[3]);
    if(inFile.is_open() && bookIn.is_open() && outFile.is_open()){
        cout << "Its Open" << endl;
    }


    JPVector<JPString*> inputJPVector;

    populateJPVectorFromInput(inputJPVector, inFile);

    parseThroughTheBook(inputJPVector, bookIn, outFile);

    for(int i = 0; i < inputJPVector.size(); i++){
        cout << *inputJPVector.at(i) << endl;
    }
    for(int i = 0; i < inputJPVector.size(); i++){
        delete inputJPVector.at(i);
    }
    inFile.close();
    return 0;
}

void populateJPVectorFromInput(JPVector<JPString*>& inputJPVector, ifstream& inFile){
    char* line = new char[80];
    JPString* jpStringRaw = nullptr;
    JPString* jpString = nullptr;
    while(!inFile.eof()){
        inFile.getline(line, 80);
        jpStringRaw = new JPString(line);

        jpString = new JPString(jpStringRaw->lowercase());

        inputJPVector.push_back(jpString);
        delete jpStringRaw;
    }
    delete[] line;
}

void parseThroughTheBook(JPVector<JPString*>& inputJPVector, ifstream& bookIn, ofstream& outFile){
    char* line = new char[256];
    int pageNumber;
    for(int i = 0; i < 100; i++) {
        bookIn.getline(line, 256);

        int r = 0;
        while (line[r] != '\0') {
            line[r] = tolower(line[r]);
            r++;
        }
        //remove all characters that are not letters
        char *token = strtok(line, " \",:;.-?!");
        //add each word to vector jpStringVec
        while (token != NULL) {
            JPString JPToken(token);
            outFile << JPToken << " ";
            token = strtok(NULL, " \",:;.-?!");
        }
        outFile << endl;
        delete [] token;
    }
    delete [] line;
}