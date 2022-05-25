

#ifndef BINARYTREE_SEARCHTREE_H
#define BINARYTREE_SEARCHTREE_H
#include <iostream>
#include <cassert>
#include "Comparable.h"
using namespace std;
class SearchTree {
private:
    struct Node { ;
        Comparable *item;
        Node *left;
        Node *right;
        int frequency;
    };
    Node *root;
    int NodeNums;

    //help to make a deep copy
    static void copyHelper(Node *cRoot, Node *&thisRoot);

    //compare helper
    bool comparingHelper(Node *otherRoot, Node *thisRoot) const;

    const Comparable *retrieveHelper(Node *curr, const Comparable &data) const;

    //display helper
    static void displayHelper(ostream &output, Node *curr);

    bool isEmpty() const;

    static void clear(Node *curr);

    int heightAddition(Node *curr) const;

    void positionFinder(Node *&newPtr, Node *curr, const Comparable &data) const;

    void deleteNode(Node *&curr);

    bool removeRecursive(Node *&curr, const Comparable &data);

    Comparable *replaceWithSmallest(Node *&curr);

    bool insertHelper(Node *curr, Comparable *newItem);

    static ostream &displaying(ostream &output, Node *curr);


    void print2DUtil(Node *root, int space);


public:
    //*************************constructors & destructors***************

    SearchTree();

    SearchTree(const SearchTree &st);

    ~SearchTree();

    //*************************overloaded operators**********************
    const SearchTree& operator=(const SearchTree& right);
    //
    bool operator==(const SearchTree& right) const;

    bool operator!=(const SearchTree &right) const;
    friend  ostream& operator<<(ostream& output, const SearchTree& st);

    //*****************************mutator functions************************
    //inserts a Comparable into the tree or increments the count if it is already in the tree.
    // This method should return false if the Comparable is found (and, thus, not inserted).
    // Ownership of the memory is transferred to the tree only if the object is not found in
    // the tree (in which case it must later be deallocated by the tree).
    bool insert(Comparable *newItem);

    //removes one occurrence of a Comparable from the tree. If it is the last occurrence,
    // remove the node. Return false if the Comparable is not found.
    bool remove(const Comparable &comp);

    //removes and deallocates all of the data from the tree.
    void makeEmpty();

    //Finds a Comparable in the tree using a key stored in the parameter.
    // This is useful for cases where the Comparable stores more than the sorting key.
    // Return nullptr if not found.
    const Comparable *retrieve(const Comparable &data) const;

    // returns the height of the node storing the Comparable in the tree.
    // A leaf has height 0. Return -1 if the Comparable is not found.
    int height(Comparable &comp) const;

    //print
    void print2D();

    int depthAddition(Node *node, Comparable &key) const;

    int depth(Comparable &comp) const;

    int getRootHeight();
};


#endif //BINARYTREE_SEARCHTREE_H
