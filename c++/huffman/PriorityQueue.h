//--------------------------------------------------------------------
// PRIORITYQUEUE.H
// Declaration and definition of the template PriorityQueue class
// Author: Olson (borrowing from a previous edition of Carrano/Henry)
//--------------------------------------------------------------------
// PriorityQueue class: 
//	Implements a priority queue using a heap with the following methods:
//		insert, deleteMin, findMin, heapify
//  The heap is stored in a vector (see the CSS 502 lecture notes)
//  Assumptions:
//	 Can only store data for which operator< exists
//	 (hence the Comparable type variable)
//--------------------------------------------------------------------

#pragma once
#include <vector>
#include "Heap.h"
using namespace std;

template <typename Comparable>
class PriorityQueue {
public:
	// Provide your own default constructor, copy constructor, operator=, and destructor
	//--------------------------------default constructor---------------
	//preconditions:none
	//postconditions: default constructor for priority queue;

	PriorityQueue(){
	    numElements = 0;
	    items.push_back(new Comparable());
	};

    //----------------- copy constructor-----------------------
    // a copy constructor
    //preconditions: pq is the same struct with *this
    //postcoditions: pq is copied into *this
    PriorityQueue(const PriorityQueue& pq){
	    this->NumElements = pq.numElements;
	    this->items = pq->items;
	}

    //-------------------------------------------------------------
    //A constructor that takes an array of Comparable pointers and
    // constructs a PriorityQueue using the (supplied) heapify method.
    //preconditions:
    //postconditions: use heapify to construct a priority queue
    PriorityQueue(Comparable* array[], int count){
        items = array;
        numElements = count;
        heapify();
    }


   //-----------------------destructors---------------------------------
   //destructor for priority queue
   //preconditions: items point to memory on the heap
   //postconditions: priority queue is deallocated, numElements is decremented.
    ~PriorityQueue(){
	  items.clear();
	  numElements = NULL;
	}


    //-------------------------------operator =------------------------
    // overload assign operator
    //preconditions: right has the same struct with this
    //postconditions: *this is assigned the same value to right
    PriorityQueue& operator=(const PriorityQueue& right){
	    if(this != right){
	        this->items.clear();
	        this->items = right->items;
	        this->numElements = right.numElements;
	    }
	    return *this;
	}


	
	//------------------------------------------------------------------------
	// insert - adds a single item to the priority queue
	// Preconditions: the initial heap has sufficient memory allocated
	//		and satisfies the heap order property
	// Postconditions: inserts the item into the queue, such that a new
	//		heap is created containing the union of the elements
	void insert(Comparable *c) {
		if (c == NULL) return;

		// Add item in position 0 (dummy position) to prevent percolating up from root 
		if (items.size() < 1) items.push_back(c);
		else items[0] = c;

		// Ensure we have enough space
		numElements++;
		while ((int) items.size() <= numElements)
			items.push_back(nullptr);

		// Percolate up
		int position = numElements;
		while (*c < *items[position / 2]) {
			items[position] = items[position / 2];
			position = position / 2;
		}
		items[position] = c;
	}

	//------------------------------------------------------------------------
	// findMin - returns a const pointer to the minimum value in the priority queue
	// Preconditions: items[0] exists if numElements is larger than zero
	// Postconditions: Returns nullptr if the heap is empty, otherwise returns
	//	the item at the root of the heap (presumably the minimum priority).
	const Comparable * findMin() const {
		if (numElements <= 0) return nullptr;
		else return items[1];
	}

	//------------------------------------------------------------------------
	// deleteMin - delete the minimum and return a pointer to it
	// Preconditions: items[0] exists if numElements is larger than zero
	// Postconditions: Returns nullptr if the heap is empty, otherwise returns
	//	the item at the root of the heap (presumably the minimum priority).
	//  That element is deleted from the heap and the heap order property is
	//  restored.
	Comparable * deleteMin() {
		if (numElements == 0) return nullptr;

		// Give memory back to user
		Comparable *toReturn = items[1];
		items[1] = items[numElements];
		numElements--;

		percolateDown(1);
		return toReturn;
	}	

	//------------------------------------------------------------------------
	// size
	// Preconditions: none
	// Postconditions: returns the size of the queue
	int size() const {
		return numElements;
	}	

	//------------------------------------------------------------------------
	// isEmpty
	// Preconditions: none
	// Postconditions: returns whether the queue is empty (zero elements)
	int isEmpty() const {
		return numElements == 0;
	}	

private:

	//------------------------------------------------------------------------
	// percolateDown - used to restore the heap order property after deleteMin
	// Preconditions: Both subtrees of the root are heaps
	// Postconditions: Restores the heap order property by shifting the root
	//  down until it reaches an appropriate node
	void percolateDown(int position) {
		int child = position * 2;
		if (child > numElements) return;
		if (child != numElements && *items[child + 1] < *items[child]) child++;
		if (*items[child] < *items[position]) {
			swap(items[child], items[position]);
			percolateDown(child);
		}
	}

	//------------------------------------------------------------------------
	// heapify - modifies any set of data into a heap
	// Preconditions: items has been allocated space for numElements pointers
	// Postconditions: The items stored form a heap
	void heapify() {
		for (int i = numElements / 2; i > 0; i--)
			percolateDown(i);
	}



	int numElements = 0;			// Number of elements in the queue
	vector <Comparable *> items;	// The elements in the priority queue stored in a heap
};