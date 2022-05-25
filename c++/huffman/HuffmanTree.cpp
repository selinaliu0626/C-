//-----------------------------------------------------------------------
//HuffmanTree.cpp
// member function definitions for HuffmanTree class
//Author: Selina Liu
//----------------------------------------------------------------------------
//HuffmanTree Class:
//For each letter, creat a small tree with a single node, and weight(the frequency),repeat until all
//nodes from a single tree:
//select the two trees with the smallest weights
//merge these trees into a new tree by adding a node that is the parent of both
// allow assign to another HuffmanTree
// allow traverse the tree and generate the code for each letter.
// the code book can be the return value or it can be pass in/out as a parameter
//-------------------------------------------------------------------------------

#include"HuffmanTree.h"
#include<string>

//**********************Constructors  & Destructors ************************

//-------------------------- Constructor ------------------------------------
// construct a single tree for every char and weight
//preconditions:  a node contains char and weight
//postconditions: a small tree about a node has constructed
HuffmanTree::HuffmanTree(char ch, int f) {
    // creat new dynamically allocated node
    Node *tempNode = new Node(ch,f);
    root = tempNode; //set temp node to root
}
// ----------------------------Constructor-----------------------------------
//combine two input huffman trees into a new tree, by add a new root node
//preconditions: two input trees is exist
//postconditions: a new tree combines the original two small trees, and the original trees are set to nullptr
HuffmanTree::HuffmanTree(char ch, int f, HuffmanTree *leftTree, HuffmanTree *rightTree) {
    Node *tempNode = new Node(ch,f);
    tempNode->left = leftTree->root;
    tempNode->right = rightTree->root;
    root = tempNode; // set the new root for the new tree
    // leave the  input trees empty
   leftTree->root = nullptr;
   rightTree->root = nullptr;
   delete leftTree;
   delete rightTree;
}
//--------------------------------copy constructors---------------------------
// deep copy to the right huffman tree
//preconditions: ht.pointer points to an HuffmanTree has root
//postconditions: ht is copied into *this
HuffmanTree::HuffmanTree(const HuffmanTree &ht) {
    root = copyHelper(ht.root);
}
//--------------------------------copy helper-------------------------------
// a private function-----copy helper, to access private date, then copy all data
//preconditions: the node is existed
//postconditions: a new Node is as same as the copyNode
HuffmanTree::Node* HuffmanTree::copyHelper(const Node *copyNode) {
    // if the node is not exist
    if(copyNode == nullptr){
        return nullptr;
    }
    Node* newNode = new Node(copyNode->c, copyNode->freq);
    newNode->left = copyHelper(copyNode->left);
    newNode->right = copyHelper(copyNode->right);
    return newNode;
}

//------------------------------destructors------------------------------
//destructor for the huffman tree
//preconditions: pointer points to memory
//postconditions: all the nodes has been cleared, the node pointer point nullptr
HuffmanTree::~HuffmanTree() {
    clearHelper(root);
    this->root = nullptr;
}
//------------------------------------clear Helper-----------------------------
//a private function----clear helper, to access private data, clear all the nodes
//preconditions: there is node here
//postconditions: clear all the nodes, release the space
void HuffmanTree::clearHelper(Node *node) {
    // if no node here,just return
    if(node == nullptr) return;
    // recursive clear
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
    node = nullptr;

}
//---------------------isLeaf------------------------
//check the node, if there is no children, it is a leaf, otherwise, not a leaf
//preconditions:  this node is exist
//postconditions: return true if it has no children, otherwise return false
bool HuffmanTree::isLeaf(Node *node){
    if(node->left == nullptr && node->right == nullptr) return true;
    return false;
}

//*********************overload operators****************************
//-------------------------operator=--------------------------------------
//assign operator: =, clear original data, copy every data from right HuffmanTree
//preconditions: the right is the same structure with *this
//postcondition: *this is assigned as same as the right HuffmanTree
HuffmanTree& HuffmanTree::operator=(const HuffmanTree &rhs) {
    //check whether two Huffman trees are same or not
    if(this != &rhs){
        //clear original data
        clearHelper(root);
        //make a deep copy to the right tree
        root = copyHelper(rhs.root);
    }
    return *this;
}
//-----------------------------------operator< --------------------------------
//This is necessary to store a HuffmanTree in the PriorityQueue.
// The ordering of the trees will be determined by the sum of the weights contained in the tree.
// If there is a tie, then tree storing the earliest character is smaller ('a' is smaller than 'z').
//preconditions:  rhs points to the same data type to *this
//postconditions: return true if the *this root frequency < rhs.root frequency, or the char is smaller
//otherwise return false
bool HuffmanTree::operator<(const HuffmanTree &rhs) const {
    if(root->freq < rhs.root->freq){
        return true;
    }else if(root->freq == rhs.root->freq){
        if(root->c < rhs.root->c ) return true;
    }
    return false;
}

//*******************************************getters ***********************************
//help  get private date

//----------------------------get char-------------------------
//get private data char
//preconditions: char is existed
//postconditions: return the char of the root
char HuffmanTree::getChar() const {
    return root->c;
}


//---------------------------get frequency---------------------------
//get the frequency
//preconditions: frequency is existed
//postconditions: return the frequency of root
int HuffmanTree::getFreq() const {
    return root->freq;
}


//***********************traverse code*********************************
//A method to traverse the tree and generate the code for each letter.
//The codebook can be the return value or it can be passed in/out as a parameter
//a public function to traverse
//preconditions:
void HuffmanTree::traverseCode(string *cBook) {
    int index = 0;
    string code = "";
    traverseHelper(root,code,index,cBook);
}
//--------------------traverseHelper-------------------------
//a private function help realize the traverse code function
//preconditions: none
//postconditions:make sure the path of all node
void HuffmanTree::traverseHelper(Node *node, string &c,int &index, string cBook[NUM_LETTERS]) {
    if(node->left != nullptr){
        c = c + "0";
        traverseHelper(node->left,c,index,cBook);
        c.pop_back();
    }
    if(node->right != nullptr){
        c = c + "1";
        traverseHelper(node->right,c,index,cBook);
        c.pop_back();
    }
    if(isLeaf(node)){
        cBook[index] = node->c +c; //remove letter once complete
        index = index + 1;
    }
}