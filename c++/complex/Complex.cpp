//link:https://replit.com/join/uyelqptavo-selinaliu3

#include <cmath>
#include "Complex.h"


Complex::~Complex() {
    //dtor
}

//setter for both data
void Complex::setComplex(double r, double i) {
    real = r;
    img = i;
}

//setter for real part
void Complex::setReal(double r) {
    real = r;
}

//setter for imaginary part
void Complex::setImaginary(double i) {
    img = i;
}

//getter for imaginary part
double Complex::getImaginary() const {
    return img;
}

//getter for real part
double Complex::getReal() const {
    return real;
}


//
// Additional checks with respect to when realNum == 0
//
void additionalChecks(char op, float imgNum) {

    if (imgNum == 0) {
        cout << "0";
    } else if (imgNum != 1 && op == '-') {
        imgNum *= -1;

        cout << imgNum << "i";
    } else if (imgNum == 1 && op == '-') {
        cout << "-i";
    } else if (imgNum == 1) {
        cout << "i";
    } else {
        cout << imgNum << "i";
    }

}

ostream &operator<<(ostream &lhs, const Complex &rhs) {

    char op;
    float realNum = rhs.real;
    float imgNum = rhs.img;


//
// Corrects any double negatives
//
    if (imgNum < 0) {
        op = '-';
        imgNum *= -1;
    } else if (imgNum >= 0) {
        op = '+';
    }

//
// Checks complex number equation format, removes
// any unnecessary output, and then displays corrected
// complex number
//
    if (realNum == 0) {

        additionalChecks(op, imgNum);

        return lhs << endl;

    } else if (imgNum == 0) {

        return lhs << realNum << endl;

    } else if (imgNum == 1) {

        return lhs << realNum << " "
                   << op << " "
                   << "i" << endl;
    } else {

        return lhs << realNum << " "
                   << op << " "
                   << imgNum << "i"
                   << endl;
    }

}


//assigns parameters with this numbers data
void Complex::getComplex(double &r, double &i) const {
    r = getReal();
    i = getImaginary();
}


//overloading comparator ==
bool operator==(const Complex &lhs, const Complex &rhs) {
    if (lhs.getReal() != rhs.getReal())
        return false;
    if (lhs.getImaginary() != rhs.getImaginary())
        return false;
    return true;
}

//overloading comparator !=
bool operator!=(const Complex &lhs, const Complex &rhs) {
    if ((lhs.getReal() != rhs.getReal()) || (lhs.getImaginary() != rhs.getImaginary()))
        return true;
    else {
        return false;
    }
}


// overloading addition operator
//(a + ib) + (c + id) = (a + c) + i(b + d)
Complex operator+(const Complex &lhs, const Complex &rhs) {
    double r = lhs.getReal() + rhs.getReal();
    double i = lhs.getImaginary() + rhs.getImaginary();
    Complex result(r, i);
    return result;
}

// overloading subtraction operator
//(a + ib) - (c + id) = (a - c) + i(b - d)
Complex operator-(const Complex &lhs, const Complex &rhs) {
    double r = lhs.getReal() - rhs.getReal();
    double i = lhs.getImaginary() - rhs.getImaginary();
    Complex result(r, i);
    return result;
}

// overloading multiplication operator
//(a + ib) * (c + id) = (ac - bd) + i(ad + bc)
Complex operator*(const Complex &lhs, const Complex &rhs) {
    double r = lhs.getReal() * rhs.getReal() - lhs.getImaginary() * rhs.getImaginary();
    double i = lhs.getReal() * rhs.getImaginary() + lhs.getImaginary() * rhs.getReal();
    Complex result(r, i);
    return result;

}

Complex operator*(const Complex &lhs, const int &rhs) {
    return Complex(lhs.getReal() * rhs, lhs.getImaginary() * rhs);
}

// overloading division operator
//(a + ib) / (c + id) = ((ac+bd)+i(bc-ad))/(c^2+d^2)
Complex operator/(const Complex &lhs, const Complex &rhs) {
    try {
        if (rhs.getReal() != 0
            || rhs.getImaginary() != 0) {
            double r = (lhs.getReal() * rhs.getReal() + lhs.getImaginary() * rhs.getImaginary()) /
                       (rhs.getReal() * rhs.getReal() + rhs.getImaginary() * rhs.getImaginary());
            double i = (lhs.getImaginary() * rhs.getReal() - lhs.getReal() * rhs.getImaginary()) /
                       (rhs.getReal() * rhs.getReal() + rhs.getImaginary() * rhs.getImaginary());
            Complex result(r, i);
            return result;
        } else {
            throw runtime_error("This is an error");
        }
    } catch (runtime_error &ex) {
        cout << "This is an error, original value is: ";
        return lhs;
    }
}


//in stream
//
// Stream Extraction operator >>
//
istream &operator>>(istream &lhs, Complex &rhs) {
    char op;

    lhs >> rhs.real >> op >> rhs.img;


    if (op == '-') {
        rhs.img *= -1;
    }

    return lhs;
}

//current object += parameter
Complex &Complex::operator+=(const Complex &c) {
    real = real + c.getReal();
    img = img + c.getImaginary();
    return *this;
}

//current object -= parameter
Complex &Complex::operator-=(const Complex &c) {
    real = real - c.getReal();
    img = img - c.getImaginary();
    return *this;
}

//current object *= parameter
Complex &Complex::operator*=(const Complex &c) {
    double newReal = (real * c.real- img * c.img);
    double newImg = (real * c.img + img * c.real);
    this->real = newReal;
    this->img = newImg;
    return *this;
}

//current object /= parameter
Complex &Complex::operator/=(const Complex &c) {
    try {
        if (c.getReal() == 0
            && c.getImaginary() == 0) {
            throw runtime_error("error");
        } else {

            double newReal = real = (real * c.getReal() + img * c.getImaginary()) /
                   (c.getReal() * c.getReal() + c.getImaginary() * c.getImaginary());
            double newImg = (img * c.getReal() - real * c.getImaginary()) /
                  (c.getReal() * c.getReal() + c.getImaginary() * c.getImaginary());
            this->real = newReal;
            this->img = newImg;
        }
        return *this;
    } catch (runtime_error &er) {
        cout << "This is an error, original value is " << endl;
        return *this;
    }
}

Complex::Complex(double a, double b) {
    real = a;
    img = b;
}

Complex Complex::conjugate() const {
    return Complex(real, -img);
}

Complex &Complex::operator*=(const int &a) {
    real = real * a;
    img = img * a;
    return *this;
}

Complex &Complex::operator/=(const int &a) {
    real = real / a;
    img = img / a;
    return *this;
}












