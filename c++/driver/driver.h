#ifndef PROGRAM2_DRIVER_H
#define PROGRAM2_DRIVER_H
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;
void openFile(ifstream& inFile, string fname);
int lcs_it(int** c,string x,string y, int m, int n);//iteration 
string backtrack(int **c, string x, string y, int m, int n);//recursion
int lcs_it_test( string x,string y, int m, int n);//iteration 
int lcs_re(string x, string y, int n, int m);//recursion

#endif //PROGRAM2_DRIVER_H
