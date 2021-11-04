//
// Created by jacks on 2/27/2020.
//
#include <iostream>
#include "JPString.h"
#include "JPVector.h"

#ifndef INC_20S_PA02_AUTOINDEXER_DRIVER_H
#define INC_20S_PA02_AUTOINDEXER_DRIVER_H

void parseThroughTheBookWithWord(JPString &, ifstream &);           //get the page number from the book by word

void parseThroughTheBookWithPhrase(JPString &, ifstream &);         //get the page number from the book by phrase

void populateJPVectorFromInput(JPVector<JPString *> &, ifstream &); //get the input from the input file and put it into a JPVector

long toPageNumber(JPString &);                                      //if the input from the book is a page number get the page number

bool isPhrase(JPString &);                                          //check if the input from the input file is a word or a phrase

void printToFile(JPVector<JPString *> &, ofstream &);               //print to the output file

void sort(JPVector<JPString *> &);                                  //use in the print to file to sort alphabetically

void swap(JPVector<JPString *> &, int, int);                        //use in the sorting function

void sortIndexes(JPVector<int> &);

void swapIndexes(JPVector<int> &, int, int);                        //use in the sorting function


#endif //INC_20S_PA02_AUTOINDEXER_DRIVER_H
