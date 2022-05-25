//
// Created by Selina Liu on 2/4/22.
//
//Vertex class
// only has a ariable in this class
// input function for how to scan data
//Help generate the format for output

#ifndef PROJECT3_VERTEX_H
#define PROJECT3_VERTEX_H

#include<iostream>
#include<string>

using namespace std;

class Vertex {
public:

    friend ostream &operator<<(ostream& output, Vertex &v);// output function
    friend istream& operator>>(istream& is, Vertex& v);// input function

private:
    char name[20];// for store the name
};

#endif //PROJECT3_VERTEX_H
