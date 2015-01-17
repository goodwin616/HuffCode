#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

/*
Blake Goodwin
11/24/14
CS 2150 - Lab 102
Lab 10 - Prelab
*/


class Node {
public:               // Constructor
    Node(char g_, int freq_);
    // bool operator <(const Node& n);
    int getFreq();
    int getChar();
    void setChildren(Node * left, Node * right);
    Node* getLeftChild();
    Node* getRightChild();

private:
    int freq;
    char g;
    Node* leftChild;
    Node* rightChild;
    friend class huffmanenc;

};

#endif