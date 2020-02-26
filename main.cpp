#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <iostream>
#include "JPString.h"
#include "JPVector.h"

using namespace std;

void parseThroughTheBookWithWord(JPString &, ifstream &);

void parseThroughTheBookWithPhrase(JPString &, ifstream &);

void populateJPVectorFromInput(JPVector<JPString *> &, ifstream &);

long toPageNumber(JPString &);

bool isPhrase(JPString &);

bool printToFile(JPVector<JPString *> &, ofstream &);

void sort(JPVector<JPString *> &inputVector);

void swap(JPVector<JPString *> &, int, int);

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
}

void populateJPVectorFromInput(JPVector<JPString *> &inputJPVector, ifstream &inFile) {
    char *line = new char[80];
    JPString *jpStringRaw = nullptr;
    JPString *jpString = nullptr;
    while (!inFile.eof()) {
        inFile.getline(line, 80);
        jpStringRaw = new JPString(line);
        jpString = new JPString(jpStringRaw->lowercase());
        inputJPVector.push_back(jpString);
        delete jpStringRaw;
    }
    delete[] line;
}

void parseThroughTheBookWithWord(JPString &jpString, ifstream &bookIn) {
    char *line = new char[256];
    int pageNumber = 0;
    bookIn.clear();                 // clear fail and eof bits
    bookIn.seekg(0, ios::beg);
    JPVector<int> indexOfJPString;
    for (int i = 0; i < 10000; i++) {
        bookIn.getline(line, 256);
        int r = 0;
        while (line[r] != '\0') {
            line[r] = tolower(line[r]);
            r++;
        }
        char *token = strtok(line, " \",:;.`?!");
        bool boolPageNumber = false;
        while (token != nullptr) {
            JPString JPToken(token);
            if (JPToken.size() > 0) {
                try {
                    boolPageNumber = JPToken[0] == '<' && JPToken[JPToken.size() - 1] == '>';
                } catch (exception& e) {
                    boolPageNumber = false;
                    cout << e.what() << endl;
                }
                if (boolPageNumber) {
                    pageNumber = toPageNumber(JPToken);
                } else if (JPToken == jpString) {
                    bool containsPageNumber = false;
                    for (int k = 0; k < indexOfJPString.size(); k++) {
                        if (pageNumber == indexOfJPString.at(k)) {
                            containsPageNumber = true;
                            k = indexOfJPString.size();
                        }
                    }
                    if (!containsPageNumber) {
                        indexOfJPString.push_back(pageNumber);
                    }
                }
            }
            token = strtok(NULL, " \",:;.`?!");
        }
        delete[] token;
    }
    jpString += ": ";
    for (int p = 0; p < indexOfJPString.size() - 1; p++) {
        jpString += indexOfJPString.at(p);
        jpString += ", ";
    }
    if (indexOfJPString.size() != 0) {
        jpString += indexOfJPString.at(indexOfJPString.size() - 1);
    } else {
        jpString += "-1";
    }
    delete[] line;
}

long toPageNumber(JPString &jpString) {
    if (jpString.size() > 2) {
        char *temp = new char[jpString.size() - 1];
        bool boolPageNumber = false;
        try {
            boolPageNumber = jpString[0] == '<' && jpString[jpString.size() - 1] == '>';
        } catch (exception &e) {
            boolPageNumber = false;
            cout << e.what() << endl;
        }
        if (boolPageNumber) {
            for (int i = 1; i < jpString.size(); i++) {
                try {
                    temp[i - 1] = jpString[i];
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
            }
        }
        int i = atoi(temp);
        delete[] temp;
        return i;
    }
    return -1;
}

void parseThroughTheBookWithPhrase(JPString &jpString, ifstream &bookIn) {
    JPVector<JPString *> tempVector;
    char *temp = new char[80];
    int e = 0;
    for (e = 0; e < jpString.size(); e++) {
        try {
            temp[e] = jpString[e];
        } catch (exception &e) {
            cout << e.what() << endl;
        }
    }
    temp[e] = '\0';
    char *JPToken = strtok(temp, " \",:;.`?!");
    while (JPToken != nullptr) {
        auto *tempJPString = new JPString(JPToken);
        tempVector.push_back(tempJPString);
        JPToken = strtok(nullptr, " \",:;.`?!");
    }
    delete[] JPToken;
    delete[] temp;
    long pageNumber = 0;
    bookIn.clear();                 // clear fail and eof bits
    bookIn.seekg(0, ios::beg);
    JPVector<int> indexOfJPString;
    JPString word1;
    int i = 0;
    char *line = new char[512];
    char *line2 = new char[512];
    bookIn.getline(line, 256);
    bookIn.getline(line2, 256);
    while (!bookIn.eof()) {
        strcat(line, " ");
        strcat(line, line2);
        int r = 0;
        while (line[r] != '\0') {
            line[r] = tolower(line[r]);
            r++;
        }
        line[r] = '\0';
        char *token = strtok(line, " \",:;.`?!\r");
        bool boolPageNumber = false;
        word1 = token;
        while (token != nullptr) {
            if (word1.size() > 0) {
                try {
                    boolPageNumber = word1[0] == '<' && word1[word1.size() - 1] == '>';
                } catch (exception& e) {
                    boolPageNumber = false;
                    cout << e.what() << endl;
                }
                if (boolPageNumber) {
                    pageNumber = toPageNumber(word1);
                } else if (word1 == *tempVector.at(0)) {
                    bool containsPageNumber = false;
                    bool isEqual = true;
                    bool isEqualToWord;
                    for (int w = 0; w < tempVector.size(); w++) {
                        word1 = token;
                        isEqualToWord = (word1 == *tempVector.at(w));
                        if (isEqualToWord) {
                            token = strtok(nullptr, " \",:;.`?!\r");
                        } else {
                            isEqual = false;
                            break;
                        }
                    }
                    for (int k = 0; k < indexOfJPString.size(); k++) {
                        if (pageNumber == indexOfJPString.at(k)) {
                            containsPageNumber = true;
                            k = indexOfJPString.size();
                        }
                    }
                    if (!containsPageNumber && isEqual) {
                        indexOfJPString.push_back(pageNumber);
                    }
                }
            }
            token = strtok(nullptr, " \",:;.`?!");
            word1 = token;
        }
        delete[] token;
        i++;
        strcpy(line, line2);
        bookIn.getline(line2, 256);
    }
    delete[] line;
    delete[] line2;

    jpString += ": ";
    for (int p = 0; p < indexOfJPString.size() - 1; p++) {
        jpString += indexOfJPString.at(p);
        jpString += ", ";
    }
    if (indexOfJPString.size() != 0) {
        jpString += indexOfJPString.at(indexOfJPString.size() - 1);
    } else {
        jpString += "-1";
    }
    for (int p = 0; p < tempVector.size(); p++) {
        delete tempVector.at(p);
    }

}

bool isPhrase(JPString &jpString) {
    for (int i = 0; i < jpString.size(); i++) {
        bool Bool = false;
        try{
            Bool = (jpString[i] == ' ' || jpString[i] == '.') && (jpString[jpString.size() - 1] != ' ');
        }catch(exception& e){
            cout << e.what() << endl;
            Bool = false;
        }
        if (Bool) {
            return true;
        }
    }
    return false;
}

bool printToFile(JPVector<JPString *> &inputVector, ofstream &outFile) {
    sort(inputVector);
    JPVector<char> letterVector;
    JPString tempJPString;
    letterVector.push_back(' ');
    for (int j = 0; j < inputVector.size(); j++) {
        try {
            tempJPString = *inputVector[j];
        }catch(exception& e){
            cout << e.what() << endl;
        }
        bool isContained = false;
        for (int k = 0; k < letterVector.size(); k++) {
            bool Bool = false;
            try{
                Bool = tempJPString[0] == letterVector[k];
            }catch(exception& e){
                cout << e.what() << endl;
                Bool = false;
            }
            if (Bool) {
                isContained = true;
                continue;
            }
        }
        if (!isContained) {
            try{
                letterVector.push_back(tempJPString[0]);
            }catch(exception& e){
                cout << e.what() << endl;
            }
        }
    }
    for (int i = 0; i < inputVector.size(); i++) {
        try {
            tempJPString = *inputVector[i];
        }catch(exception& e){
            cout << e.what() << endl;
        }
        for (int j = 0; j < letterVector.size(); j++) {
            bool Bool = false;
            try{
                Bool = tempJPString[0] == letterVector[j];
            }catch(exception& e){
                cout << e.what() << endl;
                Bool = false;
            }
            if (Bool) {
                outFile << "[";
                outFile << letterVector[j];
                outFile << "]" << endl;
                letterVector[j] = '\0';
            }
        }
        outFile << *inputVector[i] << endl;
    }
}

void sort(JPVector<JPString *> &inputVector) {
    int i, j, min_idx;

    for (i = 0; i < inputVector.size() - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < inputVector.size(); j++) {
            if ((*inputVector[j] < *inputVector[min_idx]) < 0) {
                min_idx = j;
            }
        }
        swap(inputVector, min_idx, i);
    }
}

void swap(JPVector<JPString *> &inputVector, int min_idx, int i) {
    JPString *temp = inputVector[min_idx];
    inputVector[min_idx] = inputVector[i];
    inputVector[i] = temp;
}