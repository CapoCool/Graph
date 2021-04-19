
/*
Name: Dillan Poorman
Class : CSE310
Date: 11/09/2020

Header file for graph.cpp


*/

#ifndef GRAPH_H
#define GRAPH_H

#include<string>
#include<iostream>
#include"LinkedList.h"
#include "MinHeap.h"
using namespace std;


class Project {

public:

	void setName(string name) { this->name = name; }
	string getName() { return this->name; }

private:

	string name;
};



class Graph {
	
	int numNodes; //number of nodes
	LinkedList* adjList;
	Project* nodes;

public:

	Graph();
	Graph(int numNodes);
	~Graph();

	void addNode(string name, int index);
	void addEdge(string projSrc, string projDest, int weight);
	int nodeListSearch(string proj);
	string nodeListSearch(int i);
	void printGraph();
	void shortestPath(string src, string dest, string print);


};

#endif // !GRAPH_H
