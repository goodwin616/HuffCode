// Code written by Aaron Bloomfield, 2014
// Released under a CC BY-SA license
// This code is part of the https://github.com/aaronbloomfield/pdr repository

/*
Blake Goodwin
11/24/14
CS 2150 - Lab 102
Lab 10 - Prelab
*/


#ifndef HEAP_H
#define HEAP_H

#include "node.h"
#include <vector>
using namespace std;

class heap {
public:
    // heap();
    heap(vector<Node*> vec);
    ~heap();
    void insert(Node* n);
    Node* findMin();
    Node* deleteMin();
    unsigned int size();
    void makeEmpty();
    bool isEmpty();
    void print();

private:
    vector<Node*> priorityHeap;
    unsigned int heap_size;

    void percolateUp(int hole);
    void percolateDown(int hole);
};

#endif
