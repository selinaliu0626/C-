
#include "longint.h"
using namespace std;

// constructor
LongInt::LongInt(const string str) {
    int index=0;

    //when it is negative number
    if(str[index] == '-'){
        negative = true;
        index++;
    }else
        negative = false;

    //input numbers to queue
    for(index=0;index < str.size();index++) {
        if (isdigit(str[index])) digits.addBack(str[index]);
    }

        //remove invalid 0s
    remove0s();
}

LongInt::LongInt(const LongInt &rhs) {
    negative = rhs.negative;
    digits = rhs.digits;
}

LongInt::LongInt() {
    digits.addFront('0');
    negative = false;
}

//destructor
LongInt::~LongInt() {
    negative = false;
    digits.clear();
}

//input overload
istream &operator>>(istream &in, LongInt &rhs){
    // reset everything if there is any memory leaking
    rhs.negative = false;
    rhs.digits.clear();

    //creat the string to receive the input
    string str;
    in >> str;

    int index = 0;

    //check the negative case
    if(str[index] == '-'){
        rhs.negative = true;
        index++;

    }else
        rhs.negative = false;

    //input numbers to the queue
    for(index=0;index < str.size();index++){
        if(isdigit(str[index])) rhs.digits.addBack(str[index]);
    }
    rhs.remove0s();
    return in;
}

//output overloading
ostream &operator<<(ostream &out, const LongInt &rhs){
    //copy constructor
    LongInt copy(rhs);

    //show the value
    if(copy.negative) out << "-";
    while(!copy.digits.isEmpty())
        out<< copy.digits.removeFront();
    return out;
}

//assignment operator
const LongInt& LongInt::operator=(const LongInt &rhs){
    negative = rhs.negative;
    digits = rhs.digits;
    return *this;

}

// remove 0s function
void LongInt::remove0s() {
    //check if it is "0" or 000000000
    char currentFront = this-> digits.getFront();
    if(currentFront == '0'){
        //remove all 0s in the front
        for(;currentFront == '0' && !this->digits.isEmpty(); currentFront = this->digits.removeFront());
        // push back the digit popped out before

        this->digits.addFront(currentFront);

        //make sure -0 won't happen
        if(this->digits.size() == 1 && this->digits.getFront() == '0')
            this->negative = false;
    }
}
// Function for converting char to int
int LongInt::CharToInt(const char c) const {
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        default: return 0;
    }
}

// Function for converting integer to char
char LongInt::IntToChar(const int c) const {
    switch (c) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        default: return '0';
    }
}


//arithmetic binary operator +
LongInt LongInt::operator+(const LongInt &rhs) const{
    int carry = 0;
    char digit;
    LongInt copyLhs(*this);
    LongInt copyRhs(rhs);

    //positive lhs + negative rhs means ans = lhs- rhs, should call operator "-"
    if(!copyLhs.negative && copyRhs.negative){
        copyRhs.negative = false;
        return copyLhs-copyRhs;
    }

    //negative lhs + positive rhs means ans = rhs - lhs
    if(copyLhs.negative && !copyRhs.negative){
        copyLhs.negative = false;
        return copyRhs- copyLhs;
    }

    //procedure for calculation +
    int size = (copyLhs.digits.size() <= copyRhs.digits.size()) ? copyLhs.digits.size() : copyRhs.digits.size();

    //the program will initialize the object to 0, so we need to empty the queue
    LongInt LongInt;
    LongInt.digits.clear();

    for(int i = 0;i < size; i++){
        int leftNum = CharToInt(copyLhs.digits.removeBack());
        int rightNum = CharToInt(copyRhs.digits.removeBack());
        digit = IntToChar(( leftNum + rightNum + carry ) % 10);
        LongInt.digits.addFront(digit);
        carry = (leftNum + rightNum + carry) / 10;
    }

    // if two numbers has same digits
    size = copyLhs.digits.size() - copyRhs.digits.size();
    if(size == 0){

        if( carry == 1)
            LongInt.digits.addFront(IntToChar(carry));
        // if lhs and rhs are both negative
        if(copyLhs.negative && copyRhs.negative)
            LongInt.negative = true;
        return LongInt;
    }

    //if lhs size is small than rhs
    size = (size < 0) ? (size) * (-1): size;
    for (int i = 0; i < size; i++){
        if( copyLhs.digits.size()){
            int leftNum = CharToInt(copyLhs.digits.removeBack());
            digit = IntToChar(leftNum + carry);
            LongInt.digits.addFront(digit);
            carry = (leftNum + carry) / 10;
        }else{
            int rightNum = CharToInt(copyRhs.digits.removeBack());
            digit = IntToChar(rightNum + carry);
            LongInt.digits.addFront(digit);
            carry = (rightNum + carry) / 10;
        }
    }
    //
    if(carry == 1)
        LongInt.digits.addFront(IntToChar(carry));
    // if lhs and rhs are both negative
    if(copyLhs.negative && copyRhs.negative)
        LongInt.negative = true;
    return LongInt;
}

// Arithmetic binary operators -
LongInt LongInt::operator-( const LongInt &rhs ) const {
    int borrow = 0; char digit;
    LongInt copyLhs(*this);
    LongInt copyRhs(rhs);

    // positive lhs - negative rhs means ans = lhs + rhs
    if (!copyLhs.negative && copyRhs.negative) {
        copyLhs.negative = false; copyRhs.negative = false;
        return copyLhs + copyRhs;
    }

    // negative lhs - positive rhs means ans = -(lhs + rhs). This corresponds to the 4th case of operator+.
    if (copyLhs.negative && !copyRhs.negative) {
        copyLhs.negative = false; copyRhs.negative = false;
        LongInt ans = copyLhs + copyRhs;
        ans.negative = true;
        return ans;
    }

    // negative lhs - negative rhs means ans = rhs - lhs
    if (copyLhs.negative && copyRhs.negative) {
        copyLhs.negative = false; copyRhs.negative = false;
        return copyRhs - copyLhs;
    }

    // If rhs > lhs, then swap them plus the '-'
    if (copyRhs > copyLhs) {
        LongInt ans = copyRhs - copyLhs;
        ans.negative = true;
        return ans;
    }

    // Procedure for calculation (-)
    int size = (copyLhs.digits.size() <= copyRhs.digits.size()) ? copyLhs.digits.size() : copyRhs.digits.size();

    // The program will initialize the object to 0, so we need to empty the queue
    LongInt longInt; longInt.digits.clear();

    for (int i = 0; i < size; i++) {
        int leftNum = CharToInt(copyLhs.digits.removeBack());
        int rightNum = CharToInt(copyRhs.digits.removeBack());
        if (leftNum - rightNum < 0) {
            if (borrow == 0) {
                digit = IntToChar(10 + leftNum - rightNum);
                borrow++;
                longInt.digits.addFront(digit);
            } else {
                digit = IntToChar(10 + leftNum - rightNum - borrow);
                longInt.digits.addFront(digit);
            }
        } else {
            if (leftNum - rightNum - borrow < 0) digit = IntToChar(10 + leftNum - rightNum - borrow);
            else {
                digit = IntToChar(leftNum - rightNum - borrow);
                borrow = 0;
            }
            longInt.digits.addFront(digit);
        }
    }

    // Prevent the case like "045" happened
    longInt.remove0s();

    // If the size is 0, it means that the length of both value are the same
    // If the size is 0, the below statement won't be executed
    // because i = 0 < size = 0 --> false in for statement
    // If the size != 0, it means that the case would be like 53245245 - 24435, 55452245 - 4, etc
    size = copyLhs.digits.size() - copyRhs.digits.size();
    size = (size < 0) ? (size) * (-1) : size;
    for (int i = 0; i < size; i++) {
        if (copyLhs.digits.size() >= copyRhs.digits.size()) {
            int leftNum = CharToInt(copyLhs.digits.removeBack());
            if (leftNum - borrow < 0) digit = IntToChar(10 + leftNum - borrow);
            else {
                digit = IntToChar(leftNum - borrow);
                borrow = 0;
            }
            longInt.digits.addFront(digit);
        } else {
            int rightNum = CharToInt(copyRhs.digits.removeBack());
            if (rightNum - borrow < 0) digit = IntToChar(10 + rightNum - borrow);
            else {
                digit = IntToChar(rightNum - borrow);
                borrow = 0;
            }
            longInt.digits.addFront(digit);
        }
    }

    // Prevent the case like "045" happened
    longInt.remove0s();

    return longInt;
}

//binary operator >
bool LongInt::operator > (const LongInt &rhs )const{
    //compare the size fist
    if(digits.size() > rhs.digits.size()){
        if(negative)
            return false;
        else
            return true;
    }else if(digits.size() < rhs.digits.size()){
        if(rhs.negative)
            return true;
        else
            return false;
    }else if(digits.size() == rhs.digits.size()){
        if(!negative && rhs.negative)
            return true;
        else if(negative && !rhs.negative)
            return false;
    }
    // Comparing digit by digit if those number having the same length
    LongInt copyLhs(*this);
    LongInt copyRhs(rhs);
    int leftNum, rightNum;
    while (!copyLhs.digits.isEmpty()) {
        leftNum = CharToInt(copyLhs.digits.removeFront());
        rightNum = CharToInt(copyRhs.digits.removeFront());
        if (!negative && !rhs.negative) {
            if (leftNum > rightNum) return true;
            else if (leftNum < rightNum) return false;
        } else {
            if (leftNum > rightNum) return false;
            else if (leftNum < rightNum) return true;
        }
    }

    // return false if the they're equal
    return false;
}
//logic binary operator ==
bool LongInt::operator ==(const LongInt &rhs) const {
    //compare the length of the number first
    if(digits.size() != rhs.digits.size())
        return false;
    if(negative != rhs.negative)
        return false;
    // compare digit by digit when they have same length
    LongInt copyLhs(*this);
    LongInt copyRhs(rhs);
    int left, right;
    while(!copyLhs.digits.isEmpty()){
        left = CharToInt(copyLhs.digits.removeFront());
        right = CharToInt(copyRhs.digits.removeFront());
        if(left != right)
            return false;
    }
    return true;
}
//logical binary operator !=
bool LongInt::operator!=( const LongInt & rhs ) const {
    return !(*this == rhs);
}

//logical binary operator >=
bool LongInt::operator>=( const LongInt & rhs ) const {
    return (*this > rhs || *this == rhs);
}

//logical binary operator <
bool LongInt::operator <(const LongInt &rhs) const{
    return !(*this >= rhs);
}

//logical binary operator <=
bool LongInt::operator<=( const LongInt & rhs ) const {
    return (*this < rhs) || (*this == rhs);
}





