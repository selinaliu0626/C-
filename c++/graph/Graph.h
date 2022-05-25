//
// Created by Selina on 2/4/22.
//
//  Graph class
//declare the variables and functions for this class
// it could build a graph with given vertices list
//could find shortest path and path between two vertices
// it has print function for display all the distance and path
//also contains a print function for two given vertices


#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H

#include"bits/stdc++.h"
#include "Vertex.h"

using namespace std;
class Graph {
public:
    Graph();// a default constructor
    Graph(Graph const &graph);// a copy constructor
    Graph& operator=(const Graph &graph);// overload function for =

    void buildGraph(ifstream &infile); // build a graph function
    void insertEdge(int src, int dest, int weight);// add an edge to two vertices
    void removeEdge(int src, int dest);// remove the edge between two vertices
    void findShortestPath(); // a function use Dijkstra's algorithm to find the shortest path
    void displayAll(); // a print function for display all the information
    void display(int src, int dest);// a print function for display the index,name, distance and path of source vertices and destination vertices


private:

    static const int MAX_VERTICES = 101;

    struct EdgeNode {            // can change to a class, if desired
        EdgeNode(void);

        int adjVertex;            // subscript of the adjacent vertex
        int weight;                // weight of edge
        EdgeNode *next;
    };

    struct CompareWeight {
        bool operator() (EdgeNode const& node1, EdgeNode const& node2) {
            return node1.weight > node2.weight;
        }
    };

    struct VertexNode {
        EdgeNode *edgeHead;        // head of the list of edges
        Vertex *data;        // store vertex data here
    };
    // array of VertexNodes
    VertexNode vertices[MAX_VERTICES]{};

    // table of information for Dijkstra's algorithm
    struct Table {
        bool visited;            // whether vertex has been visited
        int dist;                // shortest known distance from source
        int path;                // previous vertex in path of min dist
    };

    int size{};
    Table T[MAX_VERTICES][MAX_VERTICES]{};
    // stores visited, distance, path -
    // two dimensional in order to solve
    // for all sources
    static EdgeNode *newAdjNode(int dest, int weight);

    string getPath(int i, int j); // get path between two vertices, design to help display function
};

#endif //PROJECT3_GRAPH_H
