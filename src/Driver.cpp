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
    while (!bookIn.eof()) { //parse through the book line by line until the end
        bookIn.getline(line, 256);
        int r = 0;
        while (line[r] != '\0') { //parse through each line and make it lowercase
            line[r] = tolower(line[r]);
            r++;
        }
        char *token = strtok(line, " \",:;.`?!"); //get each word in the line and set it to token
        bool boolPageNumber;
        while (token != nullptr) { //check if the token is empty i.e. end of the line
            JPString JPToken(token);
            if (JPToken.size() > 0) { //check again if the token now JPToken is empty
                try {
                    boolPageNumber = JPToken[0] == '<' && JPToken[JPToken.size() - 1] ==
                                                          '>'; //check if the token has the possibility to be a page number
                } catch (exception &e) {
                    boolPageNumber = false;
                    cout << e.what() << endl;
                }
                if (boolPageNumber) { //if it has the possibility to be a page numeber then get the page number
                    pageNumber = toPageNumber(JPToken);
                } else if (JPToken == jpString) { //else check if the token is equal to the passed string
                    bool containsPageNumber = false;
                    for (int k = 0; k <
                                    indexOfJPString.size(); k++) { //check if the page number is already included in the page number vector
                        if (pageNumber ==
                            indexOfJPString.at(k)) { //if the page number is in the vector then break out of the loop
                            containsPageNumber = true;
                            k = indexOfJPString.size();
                        }
                    }
                    if (!containsPageNumber) { //if the page number is not in the vector then add the page number to the vector
                        indexOfJPString.push_back(pageNumber);
                    }
                }
            }
            token = strtok(NULL, " \",:;.`?!"); //get the next token
        }
        delete[] token;
    }
    sortIndexes(indexOfJPString); //sort the indexes into assending value
    jpString += ": ";
    for (int p = 0; p < indexOfJPString.size() - 1; p++) { //add each of the indexes to the JPString
        jpString += indexOfJPString.at(p);
        jpString += ", ";
    }
    if (indexOfJPString.size() != 0) { //add the last index to the end of the JPString
        jpString += indexOfJPString.at(indexOfJPString.size() - 1);
    }
    delete[] line;
}

long toPageNumber(JPString &jpString) {
    if (jpString.size() > 2) {// if the JPString can contain a page number
        char *temp = new char[jpString.size() - 1];
        bool boolPageNumber;
        try {
            boolPageNumber = jpString[0] == '<' &&
                             jpString[jpString.size() - 1] == '>'; //check again if the JPString can be a page number
        } catch (exception &e) {
            boolPageNumber = false;
            cout << e.what() << endl;
        }
        if (boolPageNumber) {//if it is in the page number format
            for (int i = 1; i < jpString.size(); i++) { //iterate through the string
                try {
                    temp[i - 1] = jpString[i]; //put everything inside the <> brackets into a temp char*
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
            }
        }
        int i = atoi(temp); //get the value of the page number
        delete[] temp;
        return i;
    }
    return -1;
}

void parseThroughTheBookWithPhrase(JPString &jpString, ifstream &bookIn) {
    JPVector<JPString *> tempVector;
    char *temp = new char[100];
    int e = 0;
    for (e = 0; e < jpString.size(); e++) { //parse through the string and set it equal to a temp
        try {
            temp[e] = jpString[e];
        } catch (exception &e) {
            cout << e.what() << endl;
        }
    }
    temp[e] = '\0';
    char *JPToken = strtok(temp, " \",:;.`?!"); //delimit the temp variable and put it into a token
    while (JPToken != nullptr) { //check if the token is a nullptr if not, add it to a vector of JPStrings
        auto *tempJPString = new JPString(JPToken);
        tempVector.push_back(tempJPString);
        JPToken = strtok(nullptr, " \",:;.`?!");
    }
    delete[] JPToken;
    delete[] temp;
    long pageNumber = 0;
    bookIn.clear(); //these two lines reset the file back to the beginning
    bookIn.seekg(0, ios::beg);
    JPVector<int> indexOfJPString;
    JPString word1;
    int i = 0;
    char *line = new char[512];
    char *line2 = new char[512];
    bookIn.getline(line, 256); //get two lines at a time
    bookIn.getline(line2, 256);
    while (!bookIn.eof()) { //parse through the book line by line
        strcat(line, " "); //these two lines concatonate two lines into one
        strcat(line, line2);
        int r = 0;
        while (line[r] != '\0') { //make the full line lowercase
            line[r] = tolower(line[r]);
            r++;
        }
        line[r] = '\0';
        char *token = strtok(line, " \",:;.`?!\r"); //delimit the line and store the value into a token.
        bool boolPageNumber;
        word1 = token;
        while (token != nullptr) { //check if the token is a nullptr
            if (word1.size() > 0) { //make sure the token, now stored in word1, is not empty
                try {
                    boolPageNumber =
                            word1[0] == '<' && word1[word1.size() - 1] == '>'; //check if the line is a page number
                } catch (exception &e) {
                    boolPageNumber = false;
                    cout << e.what() << endl;
                }
                if (boolPageNumber) { //if the line is a page number
                    pageNumber = toPageNumber(word1);
                } else if (word1 == *tempVector.at(0)) { //check if the word is in the temp vector
                    bool containsPageNumber = false;
                    bool isEqual = true;
                    bool isEqualToWord;
                    for (int w = 0; w < tempVector.size(); w++) { //parse through the temp vector
                        word1 = token;
                        isEqualToWord = (word1 == *tempVector.at(w)); //check if the word is in the temp vector
                        if (isEqualToWord) {
                            token = strtok(nullptr, " \",:;.`?!\r"); //delimit the next word and store in token
                        } else {
                            isEqual = false;
                            break;
                        }
                    }
                    for (int k = 0; k < indexOfJPString.size(); k++) { //parse through the index vector
                        if (pageNumber ==
                            indexOfJPString.at(k)) { //if the page number is in the index vector then break
                            containsPageNumber = true;
                            k = indexOfJPString.size();
                        }
                    }
                    if (!containsPageNumber &&
                        isEqual) { //if the index is not in the index vector and the phrase is equal then add it to the index vector
                        indexOfJPString.push_back(pageNumber);
                    }
                }
            }
            token = strtok(nullptr, " \",:;.`?!");
            word1 = token;
        }
        delete[] token;
        i++;
        strcpy(line, line2); //copy the second line into the first
        bookIn.getline(line2, 256); //put the next line into the "second line"
    }
    delete[] line;
    delete[] line2;

    sortIndexes(indexOfJPString); //sort the indexes in numerical order

    jpString += ": ";
    for (int p = 0; p < indexOfJPString.size() - 1; p++) { //add each index to the end of the JPString
        jpString += indexOfJPString.at(p);
        jpString += ", ";
    }
    if (indexOfJPString.size() != 0) { //add the last index to the end
        jpString += indexOfJPString.at(indexOfJPString.size() - 1);
    }
    for (int p = 0; p < tempVector.size(); p++) { //delete the elements in the temp vector to conserve memory
        delete tempVector.at(p);
    }

}

void
sortIndexes(JPVector<int> &indexVector) { //this function uses a selection sort to sort the indexes into ascending order
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

bool isPhrase(JPString &jpString) { //function to check if the input from the keyword file is a phrase
    for (int i = 0; i < jpString.size(); i++) { //parse through the string character by character
        bool Bool;
        try {
            Bool = (jpString[i] == ' ' || jpString[i] == '.') && (jpString[jpString.size() - 1] !=
                                                                  ' '); //check if the string contains a space or a period and that it does not have a space at the end
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

void printToFile(JPVector<JPString *> &inputVector,
                 ofstream &outFile) { //this function prints to the output file using the correct format
    sort(inputVector); //sort the input vector alphabetically
    JPVector<char> letterVector;
    JPString tempJPString;
    letterVector.push_back(' ');
    for (int j = 0; j < inputVector.size(); j++) { //parse through the input vector(a vector of JPString*s)
        try {
            tempJPString = *inputVector[j];
        } catch (exception &e) {
            cout << e.what() << endl;
        }
        bool isContained = false;
        for (int k = 0; k < letterVector.size(); k++) { //parse through by the letter vector
            bool Bool;
            try {
                Bool = tempJPString[0] ==
                       letterVector[k]; //check if the first letter of the JPString is in the letter vector
            } catch (exception &e) {
                cout << e.what() << endl;
                Bool = false;
            }
            if (Bool) {
                isContained = true;
                continue;
            }
        }
        if (!isContained) { //if the letter vector does not have the first letter then add it to it
            try {
                letterVector.push_back(tempJPString[0]);
            } catch (exception &e) {
                cout << e.what() << endl;
            }
        }
    }
    for (int i = 0; i < inputVector.size(); i++) { //parse through the input vector
        try {
            tempJPString = *inputVector[i];
        } catch (exception &e) {
            cout << e.what() << endl;
        }
        for (int j = 0; j <
                        letterVector.size(); j++) { //parse the letter vector and tell if the first letter of the JPString equals one of the letter vectors
            bool Bool;
            try {
                Bool = tempJPString[0] == letterVector[j];
            } catch (exception &e) {
                cout << e.what() << endl;
                Bool = false;
            }
            if (Bool) { //if the first letter of the string equals a letter vector then output it to the file in the form [CAPITAL LETTER]
                char tempChar = toupper(letterVector[j]);
                outFile << "[";
                outFile << tempChar;
                outFile << "]" << endl;
                letterVector[j] = '\0';
            }
        }
        try { //finally, output the word + the pagenumber JPString object to the output file.
            int j = 0;
            while(j < inputVector[i]->size()){ //while the iterator variable is less than each strings size
                if((j%50 != 0) || (j == 0)){ //if not divisible by 50 or is 0 then output the character at that position
                    outFile << inputVector[i]->operator[](j);
                }else{ //else output in the correct format
                    outFile << endl;
                    outFile << "    " << inputVector[i]->operator[](j);
                }
                j++;
            }
            outFile << endl;
        } catch (exception &e) {
            cout << e.what() << endl;
        }
    }
}

void sort(JPVector<JPString *> &inputVector) { //sorts the input vector in alphabetical order with a selection sort
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

void swap(JPVector<JPString *> &inputVector, int min_idx, int i) { //used by selection sort
    JPString *temp = inputVector[min_idx];
    inputVector[min_idx] = inputVector[i];
    inputVector[i] = temp;
}

void swapIndexes(JPVector<int> &inputVector, int min_idx, int i) { //used by selection sort
    int temp = inputVector[min_idx];
    inputVector[min_idx] = inputVector[i];
    inputVector[i] = temp;
}