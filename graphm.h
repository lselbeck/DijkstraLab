//-----------------------------------------------------------------------//
// GRAPHM.H                                                              //
// Author: Luke Selbeck                                                  //
// Date: April 30th, 2014                                                //
// Class: CSS 343                                                        //
//                                                                       //
// GraphM holds a graph with edges between nodes.  Uses Dijkstra's       //
// short path algorithm to find the shortest path between nodes          //
//-----------------------------------------------------------------------//
// Graph: defined as a stucture consisting of a finite set of ordered    //
//        pairs of vertices, called nodes, with edges connecting them.   //
//        An edge is said to point from one node to another.  Edges      //
//        between nodes also have costs/distances.                       //
//                                                                       //
// Implementation and assumptions:                                       //
//    -- input data file has correctly formatted data (see buildGraph)   //
//    -- all arrays start storing data at index 1, so that node numbers  //
//       are equal to index number                                       //
//    -- does not accept negative distances                              //
//                                                                       //
//-----------------------------------------------------------------------//

#ifndef GRAPHM_H
#define GRAPHM_H
#include <iostream>
#include <iomanip>
#include <limits.h>
#include "nodedata.h"
using namespace std;


class GraphM {

public:
//-------------------------- Constructor ----------------------------------
// Default constructor for class GraphM
// Preconditions:   makeEmpty re-initializes the data
// Postconditions:  all array are initialized and size is 0
GraphM();

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
// Postconditions:  nodes and edges are inputted into GraphM
void buildGraph(istream&);

//---------------------------- makeEmpty ----------------------------------
// All data members in GraphM are set back to their original values upon
// upon construction
// Preconditions:   none
// Postconditions:  all data is set to construction values
void makeEmpty();

//----------------------------- insertEdge --------------------------------
// Add an edge to GraphM, returns true if successful
// Preconditions: no negative values allowed, and only edges to and from
//       edges that already are in GraphM
// Postconditions: the new edge is added to the graph. if there already was
//       an edge from node to node, the distance is overwritten
bool insertEdge(int, int, int);

//----------------------------- removeEdge --------------------------------
// Remove an edge from GraphM, returns true if to and from nodes were in
// GraphM
// Preconditions: 
//       -- no negative values allowed, and only edges to and from
//          edges that already are in GraphM
//       -- insertEdge works properly
// Postconditions: the edge between the two nodes is removed from the
//       graph AKA reset to infinity
bool removeEdge(int, int);

//-------------------------- findShortestPath -----------------------------
// Find the shortest path from all nodes to all nodes, and fills T with
// all the information
// Preconditions: none
// Postconditions: T is filled with all pathing information between all
//       nodes
void findShortestPath();

//------------------------------ displayAll -------------------------------
// Displays through cout all of the nodes and the paths inbetween them.
// includes extra blank line at end
// Preconditions: none
// Postconditions: none
void displayAll() const;

//-------------------------------- display --------------------------------
// Displays one path from one node to another.  In order, 
// [node1] [node2] [distance] [pathing]
// [names of path nodes]
// Sample output:
//    1     4     50       1 3 2 4
//    Aurora and 85th 
//    Woodland Park Zoo 
//    Green Lake Starbucks 
//    Troll under bridge 
// 
// Preconditions: no negative values allowed, and only edges to and from
//       nodes that already are in GraphM
// Postconditions: none
void display(int, int) const;


private:

   struct TableType { 
      bool visited;  // whether node has been visited 
      int dist;      // currently known shortest distance from source 
      int path;      // previous node in path of min dist 
   }; 
   
   static const int MAXNODES = 100;

   NodeData data[MAXNODES];         // data for graph nodes information 
   int C[MAXNODES][MAXNODES];       // Cost array, the adjacency matrix 
   int size;                        // number of nodes in the graph 
   TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path 

//--------------------------- displayPathHelper ---------------------------
// Helper function for display. Displays one path from one node to another.
// Preconditions: no negative values allowed, and only edges to and from
//       nodes that already are in GraphM
// Postconditions: none
void displayPathHelper(int, int) const;

//------------------------- displayPathNamesHelper ------------------------
// Helper function for display. Displays the names of the nodes on the path
// from one node to another. Includes a trailing endl.
// Preconditions: none
// Postconditions: none
void displayPathNamesHelper(int, int) const;

};

#endif
