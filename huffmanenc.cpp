#include <iostream>
#include <stdlib.h>
#include "node.h"
#include "heap.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;
#include <stdio.h>

/*
Blake Goodwin
11/24/14
CS 2150 - Lab 102
Lab 10 - Prelab
*/

vector<string> encodings;

void encode(Node* n, vector<string> path) {
    if (n->getLeftChild() != NULL) {
        vector<string> leftPath = path;
        leftPath.push_back("0");
        encode(n->getLeftChild(), leftPath);
    }
    if (n->getRightChild() != NULL) {
        vector<string> rightPath = path;
        rightPath.push_back("1");
        encode(n->getRightChild(), rightPath);  
    }
	if (n->getRightChild() == NULL && n->getLeftChild() == NULL) {
    	string output;
    	output.push_back(n->getChar());
    	output.append(" ");
    	for (int i = 0; i < path.size(); i++) {
    		output.append(path[i]);
    	}
    	cout << output << endl;
    	encodings.push_back(output);
    	return;
    }
}

int main (int argc, char **argv) {
    if ( argc != 2 ) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }
    FILE *fp = fopen(argv[1], "r");
    if ( fp == NULL ) {
        cout << "File '" << argv[1] << "' does not exist!" << endl;
        exit(2);
    }

    int freqArray[100] = {0};
    char g;
    while ((g = fgetc(fp)) != EOF ) {
    	int charVal = (int) g;
    	freqArray[charVal-32]++;
    }
    vector<Node*> unsortHeap;

    for (int i = 0; i < 100; i++ ){
    	if (freqArray[i] != 0) {
    		char W = static_cast<char>(i+32);
    		Node* n = new Node(W, freqArray[i]);
    		unsortHeap.push_back(n);
    	}
    }

    heap HuffHeap = heap(unsortHeap);

    while (HuffHeap.size() > 1) {
    	Node * left = HuffHeap.deleteMin();
    	Node * right = HuffHeap.deleteMin();
    	Node * parent = new Node((char) 0x0, left->getFreq() + right->getFreq());
    	parent->setChildren(left, right);
    	HuffHeap.insert(parent);
    }

    Node* top = HuffHeap.deleteMin();
    vector<string> path;
    encode(top, path);
    // a nice pretty separator
    cout << "----------------------------------------" << endl;
    // rewinds the file pointer, so that it starts reading the file
    // again from the begnning
    rewind(fp);
    // read the file again, and print to the screen
    int symCount = 0;
    int distCount = encodings.size();
    int compCount = 0;
    int frequency[100] = {0};
    float cost = 0;
    

    while ( (g = fgetc(fp)) != EOF ) {
        for (int i = 0; i < encodings.size(); i++) {
            if (g == (encodings[i])[0]) {
                cout << encodings[i].substr(2) << " ";
                symCount++;
                compCount += (encodings[i].substr(2)).length();
                frequency[i]++;
                break;
            }
        }
    }

    for (int i = 0; i < encodings.size(); i++ )
        cost += ((float) (encodings[i].substr(2)).length()) * ((float)(frequency[i]) / symCount);

    float compRatio = ((float)(symCount * 8)) / ((float)compCount);

    cout << endl;
    cout << "----------------------------------------" << endl;
    cout << "There are a total of " << symCount << " symbols that are encoded." << endl;
    cout << "There are " << distCount << " distinct symbols used." << endl;
    cout << "There were " << symCount * 8 << " bits in the original file." << endl;
    cout << "There were " << compCount <<  " bits in the compressed file." << endl;
    cout << "This gives a compression ratio of " << compRatio << "." << endl;
    cout << "The cost of the Huffman tree is " << cost << " bits per character." << endl;
    // close the file
    fclose(fp);
}
