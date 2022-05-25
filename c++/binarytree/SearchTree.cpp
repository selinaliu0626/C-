
#include "SearchTree.h"
#include <string>
#include <iostream>
#include <sstream>

#define COUNT 10
using namespace std;

//***************** Constructors & Destructors **********************

//default constructor
SearchTree::SearchTree(){
    this->root = nullptr;
    this->NodeNums = 0;
}

//copy constructor
SearchTree::SearchTree(const SearchTree& st) {
    this->NodeNums = st.NodeNums;
    copyHelper(st.root, this->root);
}

//destructors
SearchTree::~SearchTree() {
    makeEmpty();
}

//***************** Overloaded Operators ******************************

//overload operators= assignment of one tree to another (deep copy)
const SearchTree& SearchTree::operator=(const SearchTree& right){
    if(right != *this) {
        //delete everything on tree
        this->makeEmpty();
        copyHelper(right.root, this->root);
        this->NodeNums = right.NodeNums;
    }
    return *this;
}
//overload operators== :two trees are equal only if they have the same data, the same structure,
// and the same number of occurrences for each comparable
bool SearchTree::operator==(const SearchTree& right) const{
    if(this->NodeNums != right.NodeNums ||this->height(*root->item) != right.height(*right.root->item)){
        return false;
    }
    return comparingHelper(right.root,this->root);
}

//overload operators!=  :checks if Trees are not equal
bool SearchTree::operator!=(const SearchTree& right) const{
    if(this->NodeNums != right.NodeNums ||this->height(*root->item) != right.height(*right.root->item)){
        return true;}
    return !comparingHelper(right.root,this->root);
}

//overload operators<< output the frequency table in sorted order. This should be an inorder traversal of your tree.
ostream& operator<<(ostream& output, const SearchTree& st){
    output << "Number of Nodes: " << st.NodeNums << endl;
    //  st.displayHelper(output,st.root);
    //output << endl;
    //return output;
    return st.displaying(output,st.root);
    // output << *st.root->dataPtr << " " << st.root->frequency << endl;

    return output;
}
// displaying trial
ostream& SearchTree::displaying(ostream &output, Node* curr){
    if(curr != nullptr){
        displaying(output, curr->left);
        output<< *curr->item <<" " << curr->frequency <<endl;
        displaying(output, curr->right);
    }
    return output;
}
//display helper
void SearchTree::displayHelper(ostream &output, Node *curr) {
    if(curr != nullptr){
        displayHelper(output, curr->left);
        output << *curr->item << " " << curr->frequency <<endl;
        displayHelper(output, curr->right);
    }
}
/*bool insert(Comparable *): inserts a Comparable into the tree or increments the count if it is already in the tree.
This method should return false if the Comparable is found (and, thus, not inserted).
Ownership of the memory is transferred to the tree only if the object is not found in the tree (in which case it must later be deallocated by the tree).
Otherwise, the calling method is responsible for de-allocation.*/
bool SearchTree::insertHelper(Node *curr, Comparable *newItem){
    if(*curr->item == *newItem){
        curr->frequency++;
        return false;
    }
    if(*newItem < *curr->item){
        if(curr->left== nullptr || curr->left->item == nullptr){
            Node *newNode = new Node;
            newNode->item = newItem;
            curr->left = newNode;
            curr->left->frequency++;
            NodeNums++;
            return true;
        }
        return insertHelper(curr->left,newItem);
    }
    if(*newItem >*curr->item){
        if(curr->right == nullptr || curr->right->item == nullptr){
            Node *newNode = new Node;
            newNode->item = newItem;
            curr->right = newNode;
            curr->right->frequency++;
            NodeNums++;
            return true;
        }
        return insertHelper(curr->right,newItem);
    }
    return false;
}
bool SearchTree::insert(Comparable* newItem){
    if(isEmpty()){
        this->root = new Node;
        this->NodeNums++;
        this->root->item = newItem;
        this->root->right = this->root->left = nullptr;
        root->frequency = 1;
        return true;
    }
    return insertHelper(this->root,newItem);
}
//bool remove(const Comparable &)
//removes one occurrence of a Comparable from the tree.
// If it is the last occurrence, remove the node. Return false if the Comparable is not found.
//Feel free to use the code from the lecture notes (it will need some adaptation).
bool SearchTree::remove(const Comparable& item){
    return removeRecursive(this->root, item);
}

bool SearchTree::removeRecursive(Node*& curr, const Comparable& data){
    if(curr!= nullptr) {
        //case 1;
        if (data == *curr->item) {
            if (curr->frequency > 1) {
                curr->frequency--;
            } else {
                deleteNode(curr);
            }
            return true;
        }
        //case 2
        if (data > *curr->item) {
            return removeRecursive(curr->right, data);
        }
            //case 3
        else if (data < *curr->item) {
            return removeRecursive(curr->left, data);
        }
    }
    return false;


}
void SearchTree::deleteNode(Node *&curr) {
    curr->item = nullptr;
    //if it is no child
    if(curr->left == nullptr &&curr->right == nullptr){
        delete curr;
        curr = nullptr;
        NodeNums--;
    }
    else if(curr->right== nullptr || curr->left == nullptr){
        Node* temp = curr;
        curr = curr->left == nullptr? curr->right: curr->left;
        delete temp;
        temp = nullptr;
        NodeNums--;
    }else{
        curr->item = replaceWithSmallest(curr);
    }
}
Comparable* SearchTree::replaceWithSmallest(Node *&curr) {
    if(curr->left ==nullptr){
        Comparable* data = curr->item;
        Node* temp = curr;
        curr = curr->right;
        delete temp;
        temp = nullptr;
        NodeNums --;
        return data;
    }else{
        return replaceWithSmallest(curr->left);
    }
}



 //void makeEmpty()
 //removes and deallocates all of the data from the tree. However, the tree is not destroyed.
 //The tree is empty, but insert can still be called.
void SearchTree::makeEmpty() {
     clear(this->root);
 }
void SearchTree::clear(Node *curr) {
    if(curr != nullptr){
        clear(curr->left);
        clear(curr->right);
        curr->item = nullptr;
        delete curr;
    }
}

//const Comparable *retrieve(const Comparable &) const
// finds a Comparable in the tree using a key stored in the parameter.
//This is useful for cases where the Comparable stores more than the sorting key.
// Return nullptr if not found.
const Comparable* SearchTree::retrieve(const Comparable& data) const{
    if(this->root != nullptr){
        return retrieveHelper(this->root,data);
    }
    return nullptr;
}

//help retrieve comparable pointer
const Comparable* SearchTree::retrieveHelper(Node *curr, const Comparable &data) const{
    //case 1 nullptr
    if(curr == nullptr){
        return nullptr;
    }
    //case 2 current item is the one we are looking for
    if(*curr->item == data){
        return curr->item;
    }
    //case 3 greater than current item
    if(data > *curr->item){
        return retrieveHelper(curr->right,data);
    }
    //case 4 lesser than current item
    else{
        return retrieveHelper(curr->left,data);
    }
}



//int height(const Comparable &) const
// returns the height of the node storing the Comparable. A leaf has height zero.
//A non-leaf has height one more than the larger of the heights of its children.
//Return -1 if the Comparable is not found.

int SearchTree::height(Comparable& comp) const{
    //if this comparable cannot find
    if(this->retrieve(comp) == nullptr){
        return -1;
    }
    if(this->root != nullptr){
        Node* locatedptr;
        this->positionFinder(locatedptr,this->root,comp);
        if(locatedptr != nullptr){
            return heightAddition(locatedptr) -1;
        }
        return -1;
    }
    return -1;
}
void SearchTree::positionFinder(Node*& newPtr,Node* curr, const Comparable &data) const{
    //case 1 curr item is target item
    if(*curr->item == data){
        newPtr = curr;
    }
    //case 2 target item greater than current
    else if (*curr->item < data){
        positionFinder(newPtr,curr->right,data);
    }
    //case 3 target item lesser than current
    else if(*curr->item > data){
        positionFinder(newPtr,curr->left,data);
    }else{
        newPtr = nullptr;
    }
}

int SearchTree::heightAddition(Node* curr)const{
    //if it is a leaf
    if(curr != nullptr){
        int left = heightAddition(curr->left);
        int right = heightAddition(curr->right);
        return 1 + max(left,right);
    }
    return 0;
}
//int depth(const Comparable &) const
// returns the depth of the node storing the Comparable in the tree.
//The root has depth 0. Return -1 if the Comparable is not found.*/
int SearchTree::depth(Comparable &comp) const {
    return depthAddition(this->root, comp);

}
int SearchTree::depthAddition(Node *node, Comparable &key) const {
    if (node == nullptr) return  -1;
    if (*node->item == key) return 0;

    int tryBranch = depthAddition(node->left, key);
    if (tryBranch == -1) tryBranch = depthAddition(node->right, key);
    if (tryBranch == -1) return -1;
    else return 1 + tryBranch;
}


// other helper methods

//copy helper, from preorder traversal
void SearchTree::copyHelper(Node* cRoot, Node* &thisRoot){
    if (cRoot != nullptr){
        // preorder copy
        thisRoot = new Node();//initial root
        thisRoot->item = new Comparable(cRoot->item->getChar());
        thisRoot->frequency = cRoot->frequency;
        copyHelper(cRoot->left,thisRoot->left);
        copyHelper(cRoot->right, thisRoot->right);
    }else{
        thisRoot = nullptr;
    }
}

//check if tree is empty
bool SearchTree::isEmpty() const {
    return this->root == nullptr;
}

//compare method helper
bool SearchTree::comparingHelper(Node* otherRoot,Node* thisRoot) const{
    //check if they are empty
    if(otherRoot == nullptr && thisRoot == nullptr){
        return true;
    }
    // one is empty, while other is not
    if(otherRoot == nullptr || thisRoot == nullptr){
        return false;
    }
    //check the item
    if(*otherRoot ->item != *thisRoot->item){
        return false;
    }
    if(otherRoot->frequency != thisRoot->frequency){
        return false;
    }
    return comparingHelper(otherRoot->left,thisRoot->left)&&
           comparingHelper(otherRoot->right,thisRoot->right);
}
void SearchTree::print2DUtil(Node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<*root->item<<"\n";

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void SearchTree::print2D()
{
    // Pass initial space count as 0
    print2DUtil(this->root, 0);
}

int SearchTree::getRootHeight() {
    return this->height(*this->root->item);
}



