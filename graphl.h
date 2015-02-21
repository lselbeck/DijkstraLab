//-----------------------------------------------------------------------//
// GRAPHL.H                                                              //
// Author: Luke Selbeck                                                  //
// Date: April 30th, 2014                                                //
// Class: CSS 343                                                        //
//                                                                       //
// GraphL holds a graph with edges between nodes. Can display graph, and //
// use breadth first search and depth first search to traverse and       //
// display the graph nodes                                               //
//-----------------------------------------------------------------------//
// Graph: defined as a stucture consisting of a finite set of ordered    //
//        pairs of vertices, called nodes, with edges connecting them.   //
//        An edge is said to point from one node to another.             //
//                                                                       //
// Implementation and assumptions:                                       //
//    -- input data file has correctly formatted data (see buildGraph)   //
//    -- all arrays start storing data at index 1, so that node numbers  //
//       are equal to index number                                       //
//                                                                       //
//-----------------------------------------------------------------------//

#ifndef GRAPHL_H
#define GRAPHL_H
#include <iostream>
#include <iomanip>
#include <limits.h>
#include "nodedata.h"
using namespace std;

struct EdgeNode { 
   int adjGraphNode; // subscript of the adjacent graph node 
   EdgeNode* nextEdge; 
}; 

struct GraphNode { // structs used for simplicity, use classes if desired 
   //name of node
   NodeData data;      //not a pointer because I don't want to deal with it
   EdgeNode* edgeHead; // head of the list of edges 
   bool visited;
}; 

class GraphL {

public:
//--------------------------- Constructor ---------------------------------
// Default constructor for class GraphL
// Preconditions:   none
// Postconditions:  all GraphNode EdgeNode* are initialized to NULL,
//          size is 0
GraphL();

//---------------------------- Destructor ---------------------------------
// Destructor for class GraphL
// Preconditions:   none
// Postconditions:  all objects are freed from memory
~GraphL();

//---------------------------- makeEmpty ----------------------------------
// All data members in GraphL are set back to their original values upon
// upon construction
// Preconditions:   none
// Postconditions:  all data is set to construction values
void makeEmpty();

//----------------------------- buildGraph --------------------------------
// Builds a tree given a .txt file as input.
// assumed input example:
//       3                    //number of nodes 
//       Aurora and 85th      //names of each node 
//       Green Lake Starbucks //equal to number of nodes
//       Woodland Park Zoo                            
//       1 2 50               //edges between each node
//       1 3 20               //[node1] [node2] [distance]  
//       2 3 10 
//       0 0 0                //input 0 0 0 to end input
// Preconditions:   none
// Assumptions: node names are less than 51 characters in length
// Postconditions:  nodes and edges are inputted into GraphL
void buildGraph(istream&);

//------------------------------ displayGraph -----------------------------
// Displays through cout all of the nodes and edges inbetween them.
// Extra blank line included, because lab3.cpp doesn't have one..
// Preconditions: none
// Postconditions: none
void displayGraph() const;

//--------------------------- depthFirstSearch ----------------------------
// Displays through cout all of the nodes in order of depth, least to 
// greatest. Extra blank line included, because lab3.cpp doesn't have one..
// Assumptions: source is node 1
// Preconditions: none
// Postconditions: none
void depthFirstSearch();


private: 

   static const int MAXNODES = 100;

   GraphNode adjList[MAXNODES];  //array containing the nodes in the graph
   
   int size;   // number of nodes in the graph 

//-------------------------- clearEdgeNodeList ----------------------------
// Helper for function makeEmpty. All objects in GraphL are deleted, and 
// size is 0
// Preconditions:   none
// Postconditions:  all data is set to construction values
void clearEdgeNodeList(EdgeNode*);

//------------------------ depthFirstSearchHelper -------------------------
// Helper for depthFirstSearch. Displays through cout all of the nodes in
// order of depth, least to greatest. Trailing endl included
// Preconditions: none
// Postconditions: none
void depthFirstSearchHelper(int);
   
};

#endif
