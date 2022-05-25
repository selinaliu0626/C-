//
// Created by Selina Liu on 2/4/22.
//

#include "Vertex.h"
using namespace std;

//-----------------------------operator<<-----------------------------------
//overloaded output operator
//preconditions:none
//postconditions:output the result of all the names
ostream &operator<<(ostream& output, Vertex &v) {
    for (int i = 0; i < 20; i++) {
        if (v.name[i] == '\0') break;
        output << v.name[i];
    }
    return output;
}

//-----------------------------operator<<-----------------------------------
//overload input operation
//preconditions: none
//postconditions: scan the file with line by line,get the information
istream &operator>>(istream &is, Vertex &v) {
    is.getline(v.name, 20);
    return is;
}