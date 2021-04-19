
/*
Dillan Poorman
dpoorman@asu.edu
11/18/2020

Pretty much the same as from assignment 4 except symmetric to max heap

*/

#include "MinHeap.h"
#include <iostream>
MinHeap::MinHeap()
{
	projectList = NULL;
	currentSize = 0;
	maxSize = 0;

}
//destructor for min
MinHeap::~MinHeap()
{
	delete[] projectList;
}
//create min
void MinHeap::create(int n)
{
	projectList = new Node[n];
	currentSize = 0;
	maxSize = n;
}

//heapify by weight...
void MinHeap::heapify(Node* list, int index)
{
	int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	
	Node temp;

	//is left child is smaller than root
	if((left < currentSize) && (list[left].weight < list[smallest].weight)){
		smallest = left;
	}

	//if right is smaller than previous smaller value
	if((right < currentSize) && (list[right].weight < list[smallest].weight)){
		smallest = right;
	}

	if(smallest != index){
		temp = list[index];
		list[index] = list[smallest];
		list[smallest] = temp;

		heapify(list, smallest);
	}

}
//build the heap keeping it O(N)
void MinHeap::buildMinHeap(Node* otherList, int sizeOfOtherList)
{
	for(int i = 0; i < sizeOfOtherList; i++){
		projectList[i] = otherList[i];
	}
	
	currentSize = sizeOfOtherList;

	for(int i = sizeOfOtherList / 2; i > 0; i--){
		heapify(projectList, i);
	}
}

//print min heap, used for debugging
void MinHeap::printMinHeap()
{

	for(int i = 0; i < this->currentSize; i++){
		cout << projectList[i].name<< endl;
		cout << projectList[i].weight<< endl;
	}
}

//exchanges nodes
void MinHeap::exchange(Node* proj1, Node* proj2)
{
	Node temp = *proj1;
	*proj1 = *proj2;
	*proj2 = temp;
}

//extracts the root and then heapifies from the bottom up
Node MinHeap::extractmin()
{
	
	Node root = projectList[0];

	projectList[0] = projectList[currentSize - 1];
	currentSize--;
	heapify(projectList, 0);
	return root;
}

//to insure the indices were kept correctly aligned, I made sure to make the index correspond with Node
//array in graphs to ensure everything was getting put into the correct place, this turned out to be
//the biggest bug in my code.
Node* MinHeap::decreaseKey(int newWeight, string name)
{
	Node temp;

	int index = searchHeap(name);

	projectList[index].weight = newWeight;
	while(index > 0 && projectList[index / 2].weight > projectList[index].weight){

		exchange(&projectList[index], &projectList[index / 2]);
		index = index / 2;
	}

	return projectList;
}

//checks to see if value is in min heap
bool MinHeap::isInMinHeap(string name){

	for(int i = 0; i < currentSize; i++){
		if(name == projectList[i].name){
			return true;
		}
	}

	return false;
}

//searches for node in the heap.
int MinHeap::searchHeap(string name){

	for(int i = 0; i < currentSize; i++){

		if(name == projectList[i].name){

			return i;

		}

	}



	return -1;

}
