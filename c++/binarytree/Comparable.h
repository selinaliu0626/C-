

#ifndef BINARYTREE_COMPARABLE_H
#define BINARYTREE_COMPARABLE_H
#include <iostream>
#include <string>

using namespace std;

class Comparable{

    friend ostream& operator<<(ostream& output, const Comparable& a);

    friend istream& operator>>(istream& input, Comparable& a);

public:

    Comparable();

    Comparable(char c);
    bool operator==(const Comparable& right) const;

    bool operator!=(const Comparable& right) const;

    bool operator<(const Comparable& right) const;

    bool operator>(const Comparable& right) const;

    char getChar();

    void setChar(char c);

private:
    char storedChar;
};
#endif //BINARYTREE_COMPARABLE_H
