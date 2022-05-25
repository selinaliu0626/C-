#include <iostream>
#include "longint.h"
using namespace std;
int main(){
    LongInt a, b, c, d, e,f,g( "-0099999999999999999999999999999999x" );
    cout << "enter for a: ";
    cin >> a;
    cout << "enter for b: ";
    cin >> b;
    cout << "enter for c: ";
    cin >> c;
    cout << "enter for d: ";
    cin >> d;
    cout << "enter for e: ";
    cin >> e;
    cout << "enter for f: ";
    cin >> f;
    cout << "enter for g: ";
    cin >> g;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
    cout << "e = " << e << endl;
    cout << "f = " << f << endl;
    cout << "g = " << g << endl;

    LongInt x = f+d;
    cout << " x = "<< f <<"+"<< d << " = " << x << endl;
    LongInt y = e - b;
    cout <<"y =" << e <<" - "<< b << " = "<< y << endl;
    cout << "x == y" << " = " << (x == y) << endl;
    cout << "x != y" <<" = " << (x != y) << endl;
    cout << a << " < " << g << " = " << ( a < g ) << endl;
    cout << f << " <= " << e << " = " << ( f <= e) <<endl;
    cout << d << " > " << b << " = " << ( d > b) <<endl;
    cout << d << " >= " << c << " = " << ( d >= c) <<endl;



}
