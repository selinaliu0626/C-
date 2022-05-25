//-------------------------------------------------------------------
//HuffmanAlgorithm.cpp
// member function definitions for HuffmanAlgorithm class
//Author: Selina Liu
//-----------------------------------------------------------------------
//HuffmanAlgorithm class:
//creat an constructor to take the frequency of each letter, construct the huffmantree and
//compute the code for each character.
// allow take in a word to encode
// allow output the letter-to-code translation table with one letter per line in alphabetical order
// followed by a space and the binary encoding from the huffman algorithm.
//--------------------------------------------------------------------------



#include "HuffmanAlgorithm.h"
#include "HuffmanTree.h"

#include <iostream>

//**********************Constructors  & Destructors ************************
//---------------------------constructors-------------------------------
//constructor for Huffman Algorithm
//preconditions:none
//postconditions: help construct the huffman tree

HuffmanAlgorithm::HuffmanAlgorithm(int (&counts)[NUM_LETTERS]) {
    for(int i = 0; i < NUM_LETTERS; i++){
        HuffmanTree *newTree = new HuffmanTree(char('a'+i), counts[i]);
        mHeap.insert(newTree);
    }

    while(mHeap.size() > 1){
        // grabs 2 min elements from heap
        HuffmanTree *leftTree = mHeap.deleteMin();
        HuffmanTree *rightTree = mHeap.deleteMin();

        //get frequency and char
        int pFreq = leftTree->getFreq() + rightTree->getFreq();
        char pC = leftTree->getChar();

        //creat parent tree with left and right children
        HuffmanTree *pTree = new HuffmanTree(pC, pFreq,leftTree,rightTree);

        //insert parent back into the heap
        mHeap.insert(pTree);
    }
    mainTree = mHeap.deleteMin();
    mainTree->traverseCode(cBook);
}

//---------------------------------DESTRUCTORS---------------------------------
//destruct the Huffman algorithm
//preconditions: maintree is existed
//postconditions: maintree is deallocated.
 HuffmanAlgorithm::~HuffmanAlgorithm(){
    delete mainTree;
    mainTree = nullptr;
}
//*******************************getters***********************************

//-----------------------------------getWord-------------------------------
//This methods takes in a word to encode.
// All letters in the word are converted to the appropriate bit strings.
//preconditions:
//postconditions: return the encoding of words
string HuffmanAlgorithm::getWord(string in) {
    string code = "";
    for (int i = 0; i < in.length(); i++) {
        code = code + getCode(in[i]);
    }
    return code;
}

//---------------------------------getCode---------------------
//get the code of the char
// preconditions: char is existed
//postcoditions: return the code for the char
string HuffmanAlgorithm::getCode(char c) {
    for(int i = 0; i < NUM_LETTERS;i++) {
        if (c == (cBook[i])[0]) return cBook[i].substr(1);
    }
    return "";
}

//-----------------------------------------operator<<-------------------------
// Output the letter-to-code translation table with one letter per line (in alphabetical order)
// followed by a space and the binary encoding from the Huffman algorithm.
//preconditions: h is existed
//postconditions: output the char and the code for it
ostream &operator<<(ostream &output, HuffmanAlgorithm &h){
    char start = 'a';
    for(int i = 0;i< NUM_LETTERS;i++){
        output << char(start + i) <<" " <<h.getCode(char('a'+i)) << endl;
    }
    return output;

}
