
/*
Dillan Poorman
dpoorman@asu.edu
11/18/2020

Graph.cpp. Contains functions relevant to graphs, creating the graph, adding node, shortest path etc.

*/

#include "Graph.h"
using namespace std;
#define INF 99999


//Constructor for graph
Graph::Graph()
{
	adjList = NULL;
	nodes = NULL;
	numNodes = 0;

}

//overloaded constructor for graph
Graph::Graph(int numNodes)
{
	adjList = new LinkedList[numNodes];
	nodes = new Project[numNodes];
	this->numNodes = numNodes;
	
}


//destructor for graph, no need to delete anything else due to minheap and linked list hacing their own
//destructors
Graph::~Graph(){
	delete[] nodes;
}


//addNode, adds a node to the graph, I should've just used a hash function, then my 
//implementation in the shortest path wouldn't be so rough
void Graph::addNode(string name, int index)
{
	if (nodes == NULL) {

		cout << "graph not created" << endl;

	}
	else {

		//creates a new graph node for node arrays
		Project* proj = new Project;
		proj->setName(name);
		nodes[index] = *proj;
	}
	
	
}

//addEdge adds an Edge to the corrosponding index of Nodes array to represent the adjacent nodes and
//adds the weight
void Graph::addEdge(string projSrc, string projDest, int weight)
{
	//incase the graph hasn't been created
	if(adjList == NULL){
		
		cout << "graph not created" << endl;

	}
	else {

		//this assume projsrc AND projDest are there, to be changed.
		int index = nodeListSearch(projSrc);
		if(index != -1){
			adjList[index].addProject(projDest, weight);
		}
		else{
			cout << "Error: Node does not exist" << endl;
		}
	}
}

//helper function used to grab corresponding indices to nodes using the name of a project
//slighty inefficient, would've been much faster to use a hashing algorithm for the indices
int Graph::nodeListSearch(string proj) 
{
	
	for (int i = 0; i < numNodes; i++) {
		if (nodes[i].getName() == proj) {
			return i;
		}
	}
	return -1;
}

//helper function used to grab the name from an index. 
string Graph::nodeListSearch(int i){

	return nodes[i].getName();
}

//prints nodes, and then corrosponding adjacency list
void Graph::printGraph()
{
	if (adjList == NULL || nodes == NULL) {
		cout << "graph not made" << endl;
	}
	else {
		cout << "The Graph Content:" << endl;
		cout << "-------------------"<< endl;
		for (int i = 0; i < numNodes; i++) {
			cout << "From: " << nodes[i].getName() << endl;
			adjList[i].printList();
			cout << endl;
		}
	}
}

//Dijkstra's algorithm, one of the most fun algorithms I have ever written
void Graph::shortestPath(string src, string dest, string print)
{
	//checks for initialization of the graph
	if(adjList == NULL || nodes == NULL){
		cout << "Error: graph not initialized" << endl;
		return;
	}

	//checks if source and dest node are in the graph
	if(nodeListSearch(src) == -1 ||  nodeListSearch(dest) == -1 ){
		cout << "Error: one or more invalid nodes" << endl;
		return;
	}

	//grabbing the number of nodes
	int V = this->numNodes;
	//set d array
	Node *dist = new Node[V];


	//set pi array
	string pi[V];
	Node vert;
	int u;

	//initialization
	for( int v = 0 ; v < V ; v++){
		dist[v].weight= INF;
		dist[v].name = nodes[v].getName();
		pi[v] = "";
	}

	//setting the distance of the src node to itself to 0
	int index = nodeListSearch(src);
	MinHeap min;

	//creating the heap
	min.create(V);
	
	//initializing the heap with the nodes
	min.buildMinHeap(dist, V);

	//making sure the src node is the root
	min.decreaseKey( 0, src);
	dist[index].weight= 0;
	
	//iterates until minheap is null
	while(min.currentSize != 0){

		//this is U, this was a change I made to make sure U was getting extracted correctly before
		//reverting to indices. I am pressed on time so, I am keeping it.
		vert = min.extractmin();

		//grabs the index of U
		u = nodeListSearch(vert.name);

		//used to iterate through the linked list, I could've made a function for this in Linked List
		//but it's like 2 lines of code. It sets crawl equal to the adjList head at U's index
		Edge* crawl = adjList[u].head;


		//iterate through the linked list adjacent to U.
		while (crawl != NULL){

			//grabs the index of the node adjacent to U
			int v = nodeListSearch(crawl->projectName);

			//makes sure the node is actually in the minHeap
			bool inHeap = min.isInMinHeap(crawl->projectName);

			//compares the current value in the distance array v, to u + the weight of the adjacent node
			//updates if it is smaller, sets the parent of v to u, then decreases the value at v in the min
			//heap 
			if (dist[v].weight > dist[u].weight + crawl->weight && inHeap == true && dist[u].weight != INF){

				dist[v].weight = dist[u].weight + crawl->weight;
				pi[v] = vert.name;
				min.decreaseKey(dist[v].weight, dist[v].name);

			}

			crawl = crawl->next;
		}
		
	}


	//if print == length, print accordingly
	if(print == "length"){

		int i = 0;
		for(; i < V; i++){
			if(dist[i].name == dest && dist[i].weight != INF){
				break;
			}

		}
		if(dist[i].name == dest && dist[i].weight != INF){
			cout << "LENGTH: " << dist[i].weight << endl;
		}
		else{
			cout << "Error: " << dest << " not reachable from " << src << endl;
		}
	}
	//if print == path print accordingly, I needed to work from the bottom up, so I used a 
	//method in the linked list to just add at the head and print it.
	else if(print == "path"){

		

		LinkedList list;
		
		int i = nodeListSearch(dest);
		while(pi[i] != ""){
			list.addProject(pi[i]);
			i = nodeListSearch(pi[i]);
		}

		if(dist[i].name == dest && dist[i].weight == INF){
			cout << "Error: " << dest << " not reachable from " << src << endl;
		}
		else{
			cout << "The shortest path:" << endl;
			list.addProject(dest, 0);
			list.printPi();
		}
		
	}
	else{
		cout << "Error: unknown print command" << endl;
	}

	delete[] dist;

}
