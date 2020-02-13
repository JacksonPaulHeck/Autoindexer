//
// Created by jacks on 1/26/2020.
//
#include <iostream>
#include "JPString.h"

using namespace std;

//Empty Constructor
JPString::JPString() {
    length = 0;
    data = new char[0];
}

//Constructor with char* as param
JPString::JPString(const char *input) {
    if (input) {
        int i = 0;
        while (input[i] != '\0' && input[i] != '\r' && input[i] != '\n') { i++; }
        length = i;
        data = new char[i];
        for (int j = 0; j < i; j++) {
            data[j] = input[j];
        }
    } else {
        length = 0;
        data = new char[0];
    }
}

//Constructor with JPString as param i.e. copyConstructor
JPString::JPString(const JPString &jpString) {
    length = jpString.size();
    data = new char[length];
    for (int i = 0; i < length; i++) {
        data[i] = jpString[i];
    }
}

//Destructor
JPString::~JPString() {
    delete[] data;
}

//Returns the size of the JPString
int JPString::size() const {
    return length;
}

//Assignment Operator
JPString &JPString::operator=(const JPString &jpString) {
    if (this == &jpString) {
        return *this;
    }
    delete[] data;
    length = jpString.size();
    data = new char[length];
    for (int i = 0; i < length; i++) {
        data[i] = jpString[i];
    }
    return *this;
}

//Assignment Operator
JPString &JPString::operator=(const char *Data) {
    if (this->data == Data) {
        return *this;
    }
    int i = 0;
    while (Data[i] != '\0') {i++;}
    length = i;
    delete[] data;
    data = new char[length];
    for (int j = 0; j < length; j++) {
        data[j] = Data[j];
    }
    return *this;
}

//Equality Comparison Operator
bool operator==(const JPString &jpString, const JPString &jpString1) {
    if (jpString.size() != jpString1.size()) {
        return false;
    }
    int len = jpString.size();
    int i = 0;
    while (i < len && jpString[i] == jpString1[i]) {
        i++;
    }
    return i == len;
}

//Equality Comparison Operator
bool operator==(const JPString &jpString, const char *jpString1) {
    return jpString == JPString(jpString1);
}

//Anti-Equality Comparison Operator
bool JPString::operator!=(char character) {
    return *this->data != character;
}

//this  = this + something else
JPString JPString::operator+=(const JPString &jpString) {
    int lengthCombo = length + jpString.size();
    char *temp = new char[lengthCombo];
    for (int i = 0; i < length; i++) {
        temp[i] = data[i];
    }
    for (int j = 0; j < jpString.size(); j++) {
        temp[length + j] = jpString[j];
    }
    delete data;
    length = lengthCombo;
    data = temp;
    return *this;
}

//Indexing Operator
char &JPString::operator[](int i) const {
    return data[i];
}

//Ostream Operator
ostream &operator<<(ostream &outStream, const JPString &jpString) {
    if (jpString.size() > 0) {
        for (int i = 0; i < jpString.size(); i++) {
            outStream << jpString[i];
        }
    } else {
        outStream << "";
    }
    return outStream;
}

//IStream Operator
istream &operator>>(istream &inStream, JPString &jpString) {
    char *temp = new char[1024];
    inStream >> temp;
    jpString = JPString(temp);
    delete[] temp;
    return inStream;
}

JPString& JPString::lowercase() {
    if(length > 0){
        char *temp = new char[length];
        int i = 0;
        while(i < length){
            temp[i] = tolower(data[i]);
            i++;
        }
        delete[] data;
        data = temp;
        return *this;
    }
    return *this;
}
