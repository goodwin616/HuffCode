// Code written by Aaron Bloomfield, 2014
// Released under a CC BY-SA license
// This code is part of the https://github.com/aaronbloomfield/pdr repository

#include <iostream>
#include "heap.h"
#include "node.h"
using namespace std;

/*
Blake Goodwin
11/24/14
CS 2150 - Lab 102
Lab 10 - Prelab
*/


// builds a heap from an unsorted vector
heap::heap(vector<Node*> vec) : heap_size(vec.size()) {
    priorityHeap = vec;
    priorityHeap.push_back(priorityHeap[0]);
    Node* n = NULL;
    priorityHeap[0] = n;
    for ( int i = heap_size/2; i > 0; i-- )
        percolateDown(i);
}

// the destructor doesn't need to do much
heap::~heap() {
}

void heap::insert(Node* n) {
    // a vector push_back will resize as necessary
    priorityHeap.push_back(n);
    // move it up into the right position
    percolateUp(++heap_size);
}

void heap::percolateUp(int hole) {
    // get the value just inserted
    Node* n = priorityHeap[hole];
    // while we haven't run off the top and while the
    // value is less than the parent...
    for ( ; (hole > 1) && (n->getFreq() < priorityHeap[hole/2]->getFreq()); hole /= 2 )
        priorityHeap[hole] = priorityHeap[hole/2]; // move the parent down
    // correct position found!  insert at that spot
    priorityHeap[hole] = n;
}

Node* heap::deleteMin() {
    // make sure the heap is not empty
    if ( heap_size == 0 )
        throw "deleteMin() called on empty heap";
    // save the value to be returned
    Node* ret = priorityHeap[1];
    // move the last inserted position into the root
    priorityHeap[1] = priorityHeap[heap_size--];
    // make sure the vector knows that there is one less element
    priorityHeap.pop_back();
    // percolate the root down to the proper position
    percolateDown(1);
    // return the old root node
    return ret;
}

void heap::percolateDown(int hole) {
    // get the value to percolate down
    Node* n = priorityHeap[hole];
    // while there is a left child...
    while ( hole*2 <= heap_size ) {
        int child = hole*2; // the left child
        // is there a right child?  if so, is it lesser?
        if ( (child+1 <= heap_size) && (priorityHeap[child+1]->getFreq() < priorityHeap[child]->getFreq()) )
            child++;
        // if the child is greater than the node...
        if ( n->getFreq() > priorityHeap[child]->getFreq() ) {
            priorityHeap[hole] = priorityHeap[child]; // move child up
            hole = child;             // move hole down
        } else
            break;
    }
    // correct position found!  insert at that spot
    priorityHeap[hole] = n;
}

Node* heap::findMin() {
    if ( heap_size == 0 )
        throw "findMin() called on empty heap";
    return priorityHeap[1];
}

unsigned int heap::size() {
    return heap_size;
}

void heap::makeEmpty() {
    heap_size = 0;
}

bool heap::isEmpty() {
    return heap_size == 0;
}

void heap::print() {
    cout << "(" << priorityHeap[0]->getFreq() << ") ";
    for ( int i = 1; i <= heap_size; i++ ) {
        cout << ((char) priorityHeap[i]->getChar()) << "=" << priorityHeap[i]->getFreq() << " ";
       // next line from from http://tinyurl.com/mf9tbgm
        bool isPow2 = (((i+1) & ~(i))==(i+1))? i+1 : 0;
        if ( isPow2 )
            cout << endl << "\t";
    }
    cout << endl;
}
