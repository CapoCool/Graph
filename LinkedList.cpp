/*
Dillan Poorman
dpoorman@asu.edu
11/18/2020

LinkedList from assignment 1, any changes are marked by EDIT
*/
#include "LinkedList.h"
//Constructor to initialize the linked list
LinkedList::LinkedList()
{
    head = NULL;
}

//Destructor
//Description: Iterates through the list, stores object in temp and then deletes it.
LinkedList::~LinkedList()
{
    Edge* temp = head;
    int count = 0;
    while (temp != NULL) {
        Edge* deleted = temp;
        temp = temp->next;
        delete deleted;
        count++;
    }
}


//Description: Adds project to the link list
//EDIT:
//Removed looking for duplicates and alphabetical sorting
bool LinkedList::addProject(string newProjectName, int weight)
{


    try {
        //allocate new project
        Edge* new_project = new Edge();

        //place data, I could've placed the data in the conditionals, but it would've been more lines of code, 
        //and inserting the data in the node first helps with readability considering the amount of flow control
        new_project->weight = weight;
        new_project->projectName = newProjectName;

        //temp pointer for comparisons
        Edge* temp;

        //base case and first case
        if (head == NULL) {
            new_project->next = head;
            head = new_project;
            return true;

        }
        else {

            temp = head;

            //find insertion point, and drops out when loop finds duplicate
            while (temp->next != NULL) {

                temp = temp->next;

            }

            //checks for duplicate, if not a duplicate then the algorithm has found the place to add
            //while keeping it alphabetized, also it deletes it when a duplicate it found 
            //to conserve memory during runtime (I think it does, it's
            //been a while since I've used C++)
            
            
            new_project->next = temp->next;
            temp->next = new_project;
            


            return true;
        }

    }
    //try catch to check for memory. (Hopefully this is the way to do it, my 240 instructor had to speed up the c++ 
    // portion due to COVID-19
    catch (const bad_alloc& e) {

        return false;
    }
}
//EDIT
//overloaded add function that takes only project name as a parameter. Adds project at head
void LinkedList::addProject(string projectName){

    try{
        Edge* newNode = new Edge();
        newNode->projectName = projectName;

        newNode->weight = 0;

        newNode->next = head;
        head = newNode;

    }
    catch(const bad_alloc& e){

        cout << "unable to allocate memory" << endl;
    }
}


//EDIT
//Helper function to print pi linked list
void LinkedList::printPi(){
    Edge* temp;
    temp = head;

    while(temp != NULL){
        cout << temp->projectName << endl;
        if(temp->next != NULL){
            cout << "->" << endl;
        }
        temp = temp->next;
    }
}

//EDIT
//makes project is in the adjacency list
bool LinkedList::projectSearch(string projName){
    if(head != NULL){
        Edge* temp;
        temp = head;

        while(temp != NULL){
            if(projName == temp->projectName){
                return true;
            }
            temp = temp->next;
        }
    }
    else{
        return false;
    }

    return false;
}
//Description: prints list
//EDIT
//made changes to fit the requirements of the assignment
void LinkedList::printList()
{
    struct Edge* current = head;

    // case where there is no list
    if (current == NULL) {
        printf("There is nothing here.");
    }
    else {
        while (current != NULL) {
            cout << "To: " << current->projectName << " with weight "
                << current->weight << endl;
            current = current->next;

        }
    }

}
