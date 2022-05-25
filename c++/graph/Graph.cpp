#include "Graph.h"
#include "fstream"
#include "bits/stdc++.h"
using namespace std;

// ------------------------defult constructor------------------------------------
Graph::Graph() = default;


//----------------------------------operator =-----------------------------
//assign right var to the left var
//preconditions: none
//postconditions:this will return the same graph with the right one, same size, same vertices list
Graph& Graph::operator=(const Graph &graph) {
    this->size = graph.size;
    for (int i = 0; i < size; i++) {
        this->vertices[i] = graph.vertices[i];
    }
}

// ------------------------copy constructor------------------------------------
//deep copy graph
//preconditions:none
//postconditon:this is equal to graph, same size, same adj list
Graph::Graph(const Graph &graph) {
   this->size = graph.size;
    for (int i = 0; i < size; i++) {
       this->vertices[i] = graph.vertices[i];
    }
}




//-------------------------------- buildGraph ---------------------------------
// Builds a graph by reading data from an ifstream
// Preconditions:  infile has been successfully opened and the file contains
//                 properly formated data (according to the program specs)
// Postconditions: One graph is read from infile and stored in the object
void Graph::buildGraph(ifstream &infile) {
    infile >> size;                          // data member stores array size
    if (infile.eof())
        return;
    infile.ignore();                         // throw away '\n' to go to next line
    infile.ignore();
    // get descriptions of vertices
    for (int v = 1; v <= size; v++) {
        vertices[v].data = new Vertex;
        infile >> *vertices[v].data;
    }

    // fill cost edge array
    int src = 1, dest = 1, weight = 1;
    for (;;) {
        infile >> src >> dest >> weight;
        if (src == 0 || infile.eof())
            break;
        insertEdge(src, dest, weight);
    }
}

//--------------------------------  newAdjNode---------------------------------
//creat a new adjacency list node
//precondition:none
//postcondition:a new adjacency list is created
Graph::EdgeNode *Graph::newAdjNode(int dest, int weight) {
    auto *newNode = (struct EdgeNode *) malloc(sizeof(struct EdgeNode));
    newNode->adjVertex = dest;
    newNode->weight = weight;
    newNode->next = nullptr;
    return newNode;
}

//--------------------------------insertEdge--------------------------------------
//insert an edge to the graph
//preconditions: exist the src and dest vertices, the weight has defined
//postconditions:the new edge between src and dest is added.
void Graph::insertEdge(int src, int dest, int weight) {
    // a new node is added  to the asj list of src
    struct EdgeNode* newNode = newAdjNode(dest, weight);
    //the node is added at the beginning
    newNode->next = vertices[src].edgeHead;
    vertices[src].edgeHead = newNode;
}

//-----------------------------remove an edge-----------------------------
//to delete the edge between (u,v), it need to traversed both of the u's adjacency list and v's
//adjacency list, then find each other in the list, and remove them.
//preconditions: exist the original edge
//postconditions: the edge between two vertices is removed.

void Graph::removeEdge(int src, int dest) {
    //traversing though the u's adj list, remove v if found
    EdgeNode* head = vertices[src].edgeHead;
    EdgeNode* pre = nullptr;
    while(head->adjVertex != dest){
        pre = head;
        head = head->next;
    }
    pre->next = head->next;
    head = nullptr;
    delete head;
}

// -----------------------------find shortest path-----------------------------
//use Dijkstra's algorithm to find the shortest path
//preconditions: none
//postconditions:find the short path from start
void Graph::findShortestPath() {
    for (int i = 1; i <= size; i++) {
        //declare a priority queue, to store the data
        priority_queue<EdgeNode, vector<EdgeNode>, CompareWeight> pq;
        //intial the distance, vistied status, and the path
        for (int v = 1; v <= size; v++) {
            T[i][v].dist = INT_MAX;
            T[i][v].visited = false;
            T[i][v].path = v;
        }
        //set 0 if start vertices is the same with end
        T[i][i].dist = 0;
        //push the first vertices
        pq.push(*newAdjNode(i, 0));
        while (!pq.empty()) {
            EdgeNode node = pq.top();
            pq.pop();
            int index = node.adjVertex;
            int minDistance = node.weight;
            T[i][index].visited = true;
            if (T[i][index].dist < minDistance) continue;
            EdgeNode* adjs = vertices[index].edgeHead;
            while (adjs != nullptr) {
                //if visited, move on the next
                if (T[i][adjs->adjVertex].visited) {
                    adjs = adjs->next;
                    continue;
                }
                int newDist = T[i][index].dist + adjs->weight;
                //if the new shortest distance has founded, set the distance to new one,and the  adjVertex is the new index for the new path
                if (newDist < T[i][adjs->adjVertex].dist) {
                    T[i][adjs->adjVertex].dist = newDist;
                    T[i][adjs->adjVertex].path = index;
                    pq.push(*newAdjNode(adjs->adjVertex, newDist));
                }
                //always find path from the adj vertices
                adjs = adjs->next;
            }
        }

    }
}

//---------------------------------------------getPath------------------------------------------
//get the path from vertices i to vertices j
//preconditions: given two vertices
//postcoditions: the path between i and j are found.
string Graph::getPath(int i, int j) {
    string res;
    while(j != i && T[i][j].visited) {
        res.append(to_string(j)).append(" ");
        j = T[i][j].path;
    }
    res.append(to_string(i));
    reverse(res.begin(), res.end());
    return res;
}

//----------------------------------------------displayALL-------------------------
//display all the information for start vertices, end vertices, their distance and the path between them
//preconditions: none
//postcoditions: the all information will be printed
void Graph::displayAll() {
    cout << "Description\t\t\tFrom\tTo\tDist\tPath" << endl;
    // first, print all the vertices
    for(int i = 1; i <= size; i++) {
        cout << *vertices[i].data << endl;
        //second, find the distance
        for (int j = 1; j <= size; j++) {
            if(i == j) continue;
            string distance;
            if(T[i][j].dist == INT_MAX) {
                distance = "--";
            } else {
                distance = to_string(T[i][j].dist);
            }
            // print all, get path from previous function
            cout << "\t\t\t\t\t" << i << "\t\t" << j << "\t" << distance << "\t\t" << getPath(i, j) << endl;
        }
    }
}

//---------------------------------------------display-------------------------------------
// a print function for get the name of two vertices, and their distance ,path
//preconditions: given two vertices
//postconditions: print the name,index, distance and path of two vertices

void Graph::display(int src, int dest) {
    string path = getPath(src, dest);
    //print the index of src and dest, and their distance, path
    cout << to_string(src) << "\t" << to_string(dest) << "\t" << to_string(T[src][dest].dist) << "\t\t" << path << endl;
    stringstream ss(path);
    int index;
    // print the name
    while(ss >> index) {
        cout << *vertices[index].data << endl;
    }
}


