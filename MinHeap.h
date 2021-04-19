/*
Dillan Poorman
CSE310
09/30/2020

Header file for MaxHeap

*/

#ifndef MINHEAP_H
#define MINHEAP_H

#include <string>
#include <cmath>
using namespace std;

// struct Project
struct Node {
    string name;
    int weight;
};

// create a MaxHeap
class MinHeap {

public:
    int maxSize;
    int currentSize;
    struct Node* projectList;

    MinHeap();
    ~MinHeap();

    void create(int n);
    void heapify(Node* list, int index);
    void buildMinHeap(Node* otherList, int sizeOfOtherList);
    void printMinHeap();
    void exchange(Node* proj1, Node* proj2);
    Node extractmin();
    Node* decreaseKey(int newCost, string print);
    bool isInMinHeap(string name);
    int searchHeap(string name);


};

#endif
