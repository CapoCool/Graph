// Assignment #1 and Assignment #7
// Name: Dillan Poorman
// ASU Email Address: dpoorman@asu.edu
// Description: Linked List class for adding, removing, changing, and printing Projects.

#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings

using namespace std;

//struct Project represents some project information
struct Edge
{
    string projectName;
    int weight;
    struct Edge* next;
};

//class LinkedList will contains a linked list of projects
class LinkedList
{

public:
    Edge* head;
    LinkedList();
    ~LinkedList();

    bool addProject(string projectName, int weight);
    void addProject(string projectName);
    void printPi();
    bool projectSearch(string projName);
    void printList();
};
