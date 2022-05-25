#include <iostream>
using namespace std;

#include "polynomial.h"

int main( )

{

    Polynomial p1;



    p1.changeCoefficient( 1, 2);

    p1.changeCoefficient( -1, 1);




    cout << "p1 = " << p1<< endl;
    cout<<"degree= "<<p1.degree()<< endl;


    Polynomial p2 = p1;
    cout<< "p2= "<< p2 << endl;

    if( p1 == p2){
        cout<< "p1==p2 is true" << endl;
    }else{
        cout<< "p1==p2 is true" << endl;
    }

    p1 += p2;
    cout<< "p1=" << p1 << endl;

    p1 -= p2;
    cout<< "p1=" << p1 << endl;

    p2.changeCoefficient( 3, 2);

    p2.changeCoefficient( -2, 1);
    cout<< "p2= "<< p2 << endl;

    if(p1 != p2){
        cout<< "p1!=p2 is true" << endl;
    }else{
        cout<< "p1!=p2 is true" << endl;
    }



    Polynomial p3 = p1 + p2;

    cout << "p3 = " << p3 << endl;

    Polynomial p4 = p2 - p1;
    cout<<"p4 = "<< p4 << endl;



}
