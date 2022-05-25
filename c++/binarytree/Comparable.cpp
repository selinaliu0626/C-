#include <iostream>
#include <string>
#include "Comparable.h"
using namespace std;


//operator ==
bool Comparable::operator==(const Comparable &rhs) const {
    return this->storedChar == rhs.storedChar;
}
//operator!=
bool Comparable::operator!=(const Comparable &rhs) const {
    return this->storedChar != rhs.storedChar;

}
//operator<
bool Comparable::operator<(const Comparable &rhs) const {
    return this->storedChar < rhs.storedChar;
}
//operator>
bool Comparable::operator>(const Comparable &rhs) const {
    return this->storedChar > rhs.storedChar;
}



//************* FRIEND OPERATORS ****************************
ostream& operator<<(ostream& output, const Comparable& comp){
    output << comp.storedChar ;
    return output;
}

istream& operator>>(istream& input, Comparable& comp){
    input >> comp.storedChar ;
    return input;
}

char Comparable::getChar() {
    return this->storedChar;
}

void Comparable::setChar(char c) {
    this->storedChar = c;
}

Comparable::Comparable() {
    this->storedChar = *new char;
}

Comparable::Comparable(char c) {
    this->storedChar = *new char;
    this->storedChar = c;
}
