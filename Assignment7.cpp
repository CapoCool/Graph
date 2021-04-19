/*
Dillan Poorman
CSE310
09/30/2020

Main for Graphs
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"



using namespace std;

int main() {


    //initialize all variables
    Graph* graph = NULL;
    int nodes, edges, weight;
    string name1, name2, src, dest, command, print;

    while (true) {

        cin >> command;

        
        if (command == "fileread") {

            cout << "Next Command: " << command << endl;

            ifstream file;
            file.open("graphInfo.txt");
            if (file.is_open()) {
                file >> nodes >> edges;
                graph = new Graph(nodes);
                for (int i = 0; i < nodes; i++) {
                    file >> name1;
                    graph->addNode(name1, i);
                }

                for (int i = 0; i < edges; i++) {
                    file >> name1 >> name2 >> weight;
                    graph->addEdge(name1, name2, weight);
                }

                file.close();
            }

        }

        else if (command == "print") {
            cout << "Next Command: " << command << endl;

            if (graph == NULL) {
                cout << "Error: graph not initialized" << endl;
            }
            else {

                graph->printGraph();
            }
        }
        
        else if (command == "quit") {
            cout << "Next Command: " << command << endl;
            return 0;
        }

        else if(command == "shortest"){
            cin >> src >> dest >> print;

            cout << "Next Command: " << command << " " <<  src << " " << dest << " " << print << endl;

            if(graph == NULL){
                cout << "Error: graph not initialized" << endl;
            }
            else{
                graph->shortestPath(src, dest, print);
            }
            
        }
        else{
            cout << "Error: invalid command" << endl;
        }
    }

}
