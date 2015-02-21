//-----------------------------------------------------------------------//
// GRAPHL.CPP                                                            //
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

#include "graphl.h"

//--------------------------- Constructor ---------------------------------
// Default constructor for class GraphL
// Preconditions:   none
// Postconditions:  all GraphNode EdgeNode* are initialized to NULL,
//          size is 0
GraphL::GraphL() {
   size = 0;
   for (int i = 0; i < MAXNODES; i++)
      adjList[i].edgeHead = NULL;
}

//---------------------------- Destructor ---------------------------------
// Destructor for class GraphL
// Preconditions:   none
// Postconditions:  all objects are freed from memory
GraphL::~GraphL() {
   makeEmpty();
}

//---------------------------- makeEmpty ----------------------------------
// All data members in GraphL are set back to their original values upon
// upon construction
// Preconditions:   none
// Postconditions:  all data is set to construction values
void GraphL::makeEmpty() {
   for (int i = 0; i <= size; i++)
      if (adjList[i].edgeHead != NULL)
         clearEdgeNodeList(adjList[i].edgeHead);
   size = 0;
}

//-------------------------- clearEdgeNodeList ----------------------------
// Helper for function makeEmpty. All objects in GraphL are deleted, and 
// size is 0
// Preconditions:   none
// Postconditions:  all data is set to construction values
void GraphL::clearEdgeNodeList(EdgeNode* cur) {
   if (cur != NULL) {
      clearEdgeNodeList(cur->nextEdge);
      delete cur;
      cur = NULL;
   }
}

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
void GraphL::buildGraph(istream& infile) {
   int fromNode, toNode;      // from and to node ends of edge
   int distance;              // distance between the nodes

   makeEmpty();               // clear the graph of memory 

   infile >> size;            // read the number of nodes
   if (infile.eof()) return;  // stop if no more data
   
   string s;                  // used to read through to end of line
   getline(infile, s);

   // read graph node information
   for (int i = 1; i <= size; i++) {
      adjList[i].data.setData(infile);
      adjList[i].edgeHead = NULL;
      adjList[i].visited = false;
   }

   // read the edge data and add to the adjacency list
   for (;;) {
      infile >> fromNode >> toNode;
      if (   (fromNode > size || toNode > size) //nodes not in graph
          || (fromNode < 0    || toNode < 0)    //nodes not in graph
          || (fromNode == 0   && toNode == 0)   //end of edge data
         )
            return;

      if (adjList[fromNode].edgeHead == NULL) { //empty list
         adjList[fromNode].edgeHead = new EdgeNode;
         adjList[fromNode].edgeHead->adjGraphNode = toNode;
         adjList[fromNode].edgeHead->nextEdge = NULL;
      } else {
         //insert new edge node at beginning of list, right after head
         EdgeNode* cur = new EdgeNode;
         cur->adjGraphNode = toNode;
         cur->nextEdge = adjList[fromNode].edgeHead;        
         adjList[fromNode].edgeHead = cur;
      }
   }
}

//------------------------------ displayGraph -----------------------------
// Displays through cout all of the nodes and edges inbetween them.
// Extra blank line included, because lab3.cpp doesn't have one..
// Preconditions: none
// Postconditions: none
void GraphL::displayGraph() const{
   cout << "Graph:" << endl;
   EdgeNode* cur;
   for (int i = 1; i <= size; i++) {
      //print node number and name
      cout << "Node " << setw(9) << left << i << adjList[i].data << endl;
      
      //print edges
      cur = adjList[i].edgeHead;
      while (cur != NULL) {
         cout << "  edge " << i << " " << cur->adjGraphNode << endl;
         cur = cur->nextEdge;
      }
   }
   cout << endl; //extra blank line
}

//--------------------------- depthFirstSearch ----------------------------
// Displays through cout all of the nodes in order of depth, least to 
// greatest. Extra blank line included, because lab3.cpp doesn't have one..
// Assumptions: source is node 1
// Preconditions: none
// Postconditions: none
void GraphL::depthFirstSearch() {
   //print and mark each graph node in adjList[i]'s edge list
   cout << "Depth First Search: ";
   for (int i = 1; i <= size; i++)
      depthFirstSearchHelper(i);
   cout << endl << endl; //extra blank line

   //reset visit values so you can call this method again if you want
   for (int i = 1; i <= size; i++)
      adjList[i].visited = false;
}

//------------------------- depthFirstSearchHelper ------------------------
// Helper for depthFirstSearch. Displays through cout all of the nodes in
// order of depth, least to greatest. Trailing endl included
// Preconditions: none
// Postconditions: none
void GraphL::depthFirstSearchHelper(int nodeIndex) {
   //print and mark visited if not visited
   if (!adjList[nodeIndex].visited) {
      adjList[nodeIndex].visited = true;
      cout << nodeIndex << " ";
   }

   if (adjList[nodeIndex].edgeHead != NULL) { //if nodeIndex has edges
      EdgeNode* cur = adjList[nodeIndex].edgeHead;

      //go to first edge node down in depth
      if (!adjList[cur->adjGraphNode].visited)
         depthFirstSearchHelper(cur->adjGraphNode);
      
      //then display other edge nodes of nodeIndex
      while (cur->nextEdge != NULL) {
         cur = cur->nextEdge;
         if (!adjList[cur->adjGraphNode].visited)
            depthFirstSearchHelper( cur->adjGraphNode);
      }
   }
}
