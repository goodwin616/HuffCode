#include "node.h"

/*
Blake Goodwin
11/24/14
CS 2150 - Lab 102
Lab 10 - Prelab
*/


Node::Node(char g_, int freq_) {
   freq = freq_;
   g = g_;
   leftChild = NULL;
   rightChild = NULL;
}

int Node::getFreq() {
	return freq;
}
int Node::getChar() {
	return g;
}

void Node::setChildren(Node * left, Node * right) {
	leftChild = left;
	rightChild = right;
}

Node* Node::getLeftChild() {
	return leftChild;
}

Node* Node::getRightChild() {
	return rightChild;
}


