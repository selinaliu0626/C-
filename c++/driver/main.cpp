//https://replit.com/join/fvraorugvy-selinaliu3
#include <iostream>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include"driver.h"


using namespace std;

void openFile(ifstream& inFile, string fname){
    inFile.open(fname);
    if(inFile.is_open()){
        cout<<"Successfully opened file"<<endl;
    }else{
        cout<<"Failed to open file"<<endl;
        exit(-1);
    }

}


int main() {
    ifstream inFile;
    string x,y;

    openFile(inFile,"./input.txt");
    while (inFile.good()) {
        if (!inFile.eof()) {
            

            getline(inFile,x);
            getline(inFile,y);
            cout<<x<<endl;
            cout<<y<<endl;
        }
    }

    inFile.close();

    if(!x.empty() && x[x.size()-1] == '\r'){
        x.pop_back();
    }
    int m=x.size();

    int n=y.size();

    int **c=new int*[m+1];
    for (int i=0; i<m+1;++i) c[i]=new int [n+1];

    int len=lcs_it(c, x, y, m, n);
    cout<<"lCS LENGTH IS "<<len<<endl;
    cout<<" LCS is "<<backtrack(c,x,y ,m, n)<<endl;
   

    cout<<"Enter trial time for iterative version(less than min(|x|,|y|)"<<endl;
    cin>>m;
    cout<<"The length of the LCS is "<<lcs_it_test(x,y, m,m)<<endl;
    cout<<"Enter trial time for recursive version(less than 20)"<<endl;
    cin>>n;
    cout << "The length of the LCS is " << lcs_re(x, y, n,n) << endl;
    

    return 0;
}
