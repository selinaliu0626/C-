//https://replit.com/join/uyelqptavo-selinaliu3
#ifndef COMPLEX_H
#define COMPLEX_H

#include<iostream>
#include<string>
#include<sstream>
#include<regex>
using namespace std;

class Complex
{
private:
    double real; //for real part
    double img; //for imaginary part

public:

    explicit Complex(double =0.0,double = 0.0); //default constructor
    virtual ~Complex(); //destructor

    //setters
    void setComplex(double r,double i);
    void setReal(double r);
    void setImaginary(double i);

    //getters for data members
    double getImaginary() const;
    double getReal() const;
    void getComplex(double &r,double &i) const;

    string toString() const; //returns string form of this number

    //overloading operators
    friend Complex operator+(const Complex& lhs, const Complex& rhs); //addition
    friend Complex operator-(const Complex& lhs, const Complex& rhs); //subtraction
    friend Complex operator*(const Complex& lhs, const Complex& rhs); //multiplication
    friend Complex operator/(const Complex& lhs, const Complex& rhs); //division

    friend Complex operator*(const Complex& lhs, const int& rhs); //multiplication
    //conjugate
    Complex conjugate() const;
    //boolean comparison operators
    friend bool operator==(const Complex& lhs, const Complex& rhs); // compare equal
    friend bool operator!=(const Complex& lhs, const Complex& rhs); // compare unequal

    //assignment operators
    Complex & operator+=( const Complex &);//current object += parameter
    Complex & operator-=( const Complex &);//current object -= parameter
    Complex & operator*=( const Complex &);//current object *= parameter
    Complex & operator/=( const Complex &);//current object /= parameter
    Complex & operator*=( const int &);//current object *= parameter
    Complex & operator/=( const int &);//current object /= parameter

    //Stream I/O
    friend istream &operator>>( istream &lhs, Complex &rhs );
    friend ostream &operator<<( ostream &lhs, const Complex &rhs );

};

#endif // CO