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
    if(argc == 1) {
        Catch::Session().run();
    }
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
    int pageNumber = 0;
    for (int j = 0; j < inputJPVector.size(); j++) {
        bookIn.clear();                 // clear fail and eof bits
        bookIn.seekg(0, ios::beg);
        JPVector<int> indexOfJPString;
        for (int i = 0; i < 1000; i++) {
            bookIn.getline(line, 256);
            int r = 0;
            while (line[r] != '\0') {
                line[r] = tolower(line[r]);
                r++;
            }
            char *token = strtok(line, " \",:;.-?!");
            while (token != NULL) {
                JPString JPToken(token);
                if (JPToken.size() > 0) {
                    if (JPToken[0] == '<' && JPToken[JPToken.size() - 1] == '>') {
                        pageNumber = JPToken.toPageNumber();
                    }else if(JPToken == *inputJPVector.at(j)){
                        bool containsPageNumber = false;
                        for(int k = 0; k < indexOfJPString.size(); k++){
                            if(pageNumber == indexOfJPString.at(k)){
                                containsPageNumber = true;
                                k = indexOfJPString.size();
                            }
                        }
                        if(!containsPageNumber){
                            indexOfJPString.push_back(pageNumber);
                        }
                    }
                }
                token = strtok(NULL, " \",:;.-?!");
            }
            delete[] token;
        }
        outFile << *inputJPVector.at(j) << ": ";
        for(int p = 0; p < indexOfJPString.size()-1; p++){
               outFile << indexOfJPString.at(p) << ", ";
        }
        outFile << indexOfJPString.at(indexOfJPString.size()-1) << endl;
    }
    delete [] line;
}