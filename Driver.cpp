//
// Created by jacks on 2/27/2020.
//

#include "Driver.h"
#include <iostream>
#include <fstream>
#include "JPString.h"
#include "JPVector.h"

void populateJPVectorFromInput(JPVector<JPString *> &inputJPVector, ifstream &inFile) {
    //creation of variables used in the function
    char *line = new char[100];
    JPString *jpStringRaw = nullptr;
    JPString *jpString = nullptr;
    while (!inFile.eof()) {
        inFile.getline(line, 100);
        //check if the line is empty
        if (strcmp(line, "\0") == 0) { break; }
        //create JPString from line char*
        jpStringRaw = new JPString(line);
        //create lowercase version of JPString
        jpString = new JPString(jpStringRaw->lowercase());
        //Add the lowercase JPString to the input keyword JPVector
        inputJPVector.push_back(jpString);
        delete jpStringRaw;
    }
    delete[] line;
}

void parseThroughTheBookWithWord(JPString &jpString, ifstream &bookIn) {
    //setup variables to be used throughout function
    char *line = new char[256];
    int pageNumber = 0;
    JPVector<int> indexOfJPString;
    bookIn.clear(); //reset the bookIn ifstream in case it has been called and the line runner has been moved
    bookIn.seekg(0, ios::beg);
    int i = 0;
    while(!bookIn.eof()) {
        bookIn.getline(line, 256);
        int r = 0;
        while (line[r] != '\0') {
            line[r] = tolower(line[r]);
            r++;
        }
        char *token = strtok(line, " \",:;.`?!");
        bool boolPageNumber;
        while (token != nullptr) {
            JPString JPToken(token);
            if (JPToken.size() > 0) {
                try {
                    boolPageNumber = JPToken[0] == '<' && JPToken[JPToken.size() - 1] == '>';
                } catch (exception &e) {
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
        i++;
    }
    sortIndexes(indexOfJPString);
    jpString += ": ";
    for (int p = 0; p < indexOfJPString.size() - 1; p++) {
        jpString += indexOfJPString.at(p);
        jpString += ", ";
    }
    if (indexOfJPString.size() != 0) {
        jpString += indexOfJPString.at(indexOfJPString.size() - 1);
    }
    delete[] line;
}

long toPageNumber(JPString &jpString) {
    // if the JPString can contain a page number
    if (jpString.size() > 2) {
        char *temp = new char[jpString.size() - 1];
        bool boolPageNumber;
        try {
            boolPageNumber = jpString[0] == '<' && jpString[jpString.size() - 1] == '>';
        } catch (exception &e) {
            boolPageNumber = false;
            cout << e.what() << endl;
        }
        //if it is in the page number format
        if (boolPageNumber) {
            for (int i = 1; i < jpString.size(); i++) {
                try {
                    //put everything inside the <> brackets into a temp char*
                    temp[i - 1] = jpString[i];
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
            }
        }
        //get the value of the page number
        int i = atoi(temp);
        delete[] temp;
        return i;
    }
    return -1;
}

void parseThroughTheBookWithPhrase(JPString &jpString, ifstream &bookIn) {
    JPVector<JPString *> tempVector;
    char *temp = new char[100];
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
        bool boolPageNumber;
        word1 = token;
        while (token != nullptr) {
            if (word1.size() > 0) {
                try {
                    boolPageNumber = word1[0] == '<' && word1[word1.size() - 1] == '>';
                } catch (exception &e) {
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

    sortIndexes(indexOfJPString);

    jpString += ": ";
    for (int p = 0; p < indexOfJPString.size() - 1; p++) {
        jpString += indexOfJPString.at(p);
        jpString += ", ";
    }
    if (indexOfJPString.size() != 0) {
        jpString += indexOfJPString.at(indexOfJPString.size() - 1);
    }
    for (int p = 0; p < tempVector.size(); p++) {
        delete tempVector.at(p);
    }

}

void sortIndexes(JPVector<int> & indexVector) {
    int i, j, min_idx;

    for (i = 0; i < indexVector.size() - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < indexVector.size(); j++) {
            if ((indexVector[j] < indexVector[min_idx])) {
                min_idx = j;
            }
        }
        swapIndexes(indexVector, min_idx, i);
    }
}

bool isPhrase(JPString &jpString) {
    for (int i = 0; i < jpString.size(); i++) {
        bool Bool;
        try {
            Bool = (jpString[i] == ' ' || jpString[i] == '.') && (jpString[jpString.size() - 1] != ' ');
        } catch (exception &e) {
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
        } catch (exception &e) {
            cout << e.what() << endl;
        }
        bool isContained = false;
        for (int k = 0; k < letterVector.size(); k++) {
            bool Bool;
            try {
                Bool = tempJPString[0] == letterVector[k];
            } catch (exception &e) {
                cout << e.what() << endl;
                Bool = false;
            }
            if (Bool) {
                isContained = true;
                continue;
            }
        }
        if (!isContained) {
            try {
                letterVector.push_back(tempJPString[0]);
            } catch (exception &e) {
                cout << e.what() << endl;
            }
        }
    }
    for (int i = 0; i < inputVector.size(); i++) {
        try {
            tempJPString = *inputVector[i];
        } catch (exception &e) {
            cout << e.what() << endl;
        }
        for (int j = 0; j < letterVector.size(); j++) {
            bool Bool;
            try {
                Bool = tempJPString[0] == letterVector[j];
            } catch (exception &e) {
                cout << e.what() << endl;
                Bool = false;
            }
            if (Bool) {
                char tempChar = toupper(letterVector[j]);
                outFile << "[";
                outFile << tempChar;
                outFile << "]" << endl;
                letterVector[j] = '\0';
            }
        }
        try {
            outFile << *inputVector[i] << endl;
        } catch (exception &e) {
            cout << e.what() << endl;
        }
    }
}

void sort(JPVector<JPString *> &inputVector) {
    int i, j, min_idx;

    for (i = 0; i < inputVector.size() - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < inputVector.size(); j++) {
            if ((*inputVector[j] < *inputVector[min_idx])) {
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

void swapIndexes(JPVector<int> &inputVector, int min_idx, int i) {
    int temp = inputVector[min_idx];
    inputVector[min_idx] = inputVector[i];
    inputVector[i] = temp;
}