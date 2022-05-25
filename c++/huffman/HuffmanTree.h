//------------------------------------------------------------------------------
//HuffmanTree.h
//HuffmanTree Class
//Created by Selina Liu
//--------------------------------------------------------------------------------
//HuffmanTree Class:
//For each letter, creat a small tree with a single node, and weight(the frequency),repeat until all
//nodes from a single tree:
//select the two trees with the smallest weights
//merge these trees into a new tree by adding a node that is the parent of both
// allow assign to another HuffmanTree
// allow traverse the tree and generate the code for each letter.
// the code book can be the return value or it can be pass in/out as a parameter
//--------------------------------------------------------------------------------



#ifndef HUFFMAN_HUFFMANTREE_H
#define HUFFMAN_HUFFMANTREE_H
#include "PriorityQueue.h"
#include<iostream>

using namespace std;
const int NUM_LETTERS = 26; //AMOUNT OF CHARACTERS STARTING FOR "A" IN ASCII

class HuffmanTree {
private:
    struct Node {
        char c;      //store the char
        int freq;    // the frequency of  the char
        Node *left;  // left child pointer
        Node *right; //right  child pointer

        Node(char ch, int f) : c(ch), freq(f), left(nullptr), right(nullptr) {}
    };

    Node *root; //root node of Huffman tree

    //---------------------------------------clearHelper-------------------------
    // help clear the struct
    //preconditions: there is node here
    //postconditions: clear all the nodes, release the space
    void clearHelper(Node *node);

    //------------------------------------copy Helper-----------------------------
    // help to make a deep copy of node
    //preconditions:
    Node *copyHelper(const Node *copyNode);

    //--------------------traverseHelper-------------------------
    //a private function help realize the traverse code function
    //preconditions:node not points nullptr
    //postconditions:generate the node for each letter
    void traverseHelper(Node *node, string &c, int &index, string cBook[NUM_LETTERS]);


public:
    //*************************constructors & destructors***************

    //-------------------------- Constructor ------------------------------------
    // construct a single tree for every char and weight
    //preconditions:  a node contains char and weight
    //postconditions: a small tree about a node has constructed
    HuffmanTree(char ch, int f);

    // ----------------------------Constructor-----------------------------------
    //combine two input huffman trees into a new tree, by add a new root node
    //preconditions: two input trees is exist
    //postconditions: a new tree combines the original two small trees, and the original trees are set to nullptr
    HuffmanTree(char ch, int f, HuffmanTree *leftTree, HuffmanTree *rightTree);

    //--------------------------------copy constructors---------------------------
    // deep copy to the right huffman tree
    //preconditions: ht.pointer points to an HuffmanTree has root
    //postconditions: ht is copied into *this
    HuffmanTree(const HuffmanTree &ht);


    //------------------------------destructors------------------------------
    //destructor for the huffman tree
    //preconditions: pointer points to memory
    //postconditions: all the nodes has been cleared, the node pointer point nullptr

    ~HuffmanTree();

    //*************************overloaded operators**********************

    //-------------------------operator=--------------------------------------
    //assign operator: =, clear original data, copy every data from right HuffmanTree
    //preconditions: the right is the same structure with *this
    //postcondition: *this is assigned as same as the right HuffmanTree
    HuffmanTree &operator=(const HuffmanTree &rhs);
    //-----------------------------------operator< --------------------------------
    //This is necessary to store a HuffmanTree in the PriorityQueue.
    // The ordering of the trees will be determined by the sum of the weights contained in the tree.
    // If there is a tie, then tree storing the earliest character is smaller ('a' is smaller than 'z').
    //preconditions:  rhs points to the same data type to *this
    //postconditions: return true if the *this root frequency < rhs.root frequency, or the char is smaller
    //otherwise return false
    bool operator<(const HuffmanTree &rhs) const;

    //***************************getters***********************

    //----------------------------get char-------------------------
    //get private data char
    //preconditions: char is existed
    //postconditions: return the char of the root
    char getChar() const;

    //---------------------------get frequency---------------------------
    //get the frequency
    //preconditions: frequency is existed
    //postconditions: return the frequency of root
    int getFreq() const;

    //traverse
    void traverseCode(string cBook[NUM_LETTERS]);

    // check is it a leaf
    //---------------------isLeaf------------------------
    //check the node, if there is no children, it is a leaf, otherwise, not a leaf
    //preconditions:  this node is exist
    //postconditions: return true if it has no children, otherwise return false
    bool isLeaf(Node *node);
};



#endif //HUFFMAN_HUFFMANTREE_H
