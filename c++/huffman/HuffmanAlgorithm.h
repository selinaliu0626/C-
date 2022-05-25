//--------------------------------------------------------
//HuffmanAlgorithm.cpp
//HuffmanAlgorithm class
//Author: Selina Liu



#ifndef HUFFMAN_HUFFMANALGORITHM_H
#define HUFFMAN_HUFFMANALGORITHM_H

#include "HuffmanTree.h"
#include "Heap.h"
#include<iostream>

using namespace std;

class HuffmanAlgorithm {
public:
    //---------------------------constructors-------------------------------
    //constructor for Huffman Algorithm
    //preconditions:none
    //postconditions: help construct the huffman tree
    HuffmanAlgorithm(int (&counts)[NUM_LETTERS]);

    //-----------------------------------getWord-------------------------------
    //This methods takes in a word to encode.
    // All letters in the word are converted to the appropriate bit strings.
    //preconditions:
    //postconditions: return the encoding of words
    string getWord(string in);

    //-----------------------------------------operator<<-------------------------
    // Output the letter-to-code translation table with one letter per line (in alphabetical order)
    // followed by a space and the binary encoding from the Huffman algorithm.
    //preconditions: h is existed
    //postconditions: output the char and the code for it
    friend ostream &operator<<(ostream &output, HuffmanAlgorithm &h);

    //---------------------------------DESTRUCTORS---------------------------------
    //destruct the Huffman algorithm
    //preconditions: maintree is existed
    //postconditions: maintree is deallocated.
    ~HuffmanAlgorithm();


    //---------------------------------getCode---------------------
    //get the code of the char
    // preconditions: char is existed
    //postcoditions: return the code for the char
    string getCode(char c);

private:
    Heap<HuffmanTree> mHeap;  //min heap to hold various trees
    HuffmanTree *mainTree; // main huffman tree pointer
    string cBook[NUM_LETTERS]; //list to hold codes for chars


};

#endif //HUFFMAN_HUFFMANALGORITHM_H
