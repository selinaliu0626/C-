/*
* Polynomial.cpp
*/

#include "polynomial.h"

//initial list and creat an dummy head
Polynomial::Polynomial() {
    this->size = 0;
    this->head = nullptr;
}

// deep copy of original link representation
Polynomial::Polynomial(const Polynomial &p) {
    this->head = nullptr;
    this->size = 0;
    Term *current = p.head;
    do {
        changeCoefficient(current->coeff, current->power);
        current = current->next;
    } while (current != p.head);
}

//destructor
Polynomial::~Polynomial() {
    if (!this->head)
        return;
    Term *previous = this->head;
    Term *current = this->head;
    do {
        previous = current;
        current = current->next;
        delete (previous);
    } while (current->next != this->head);
    this->head = nullptr;

}

// return the degree of polynomial
int Polynomial::degree() const {
    if (!head)
        return -1;
    return head->power;
}

//return the coefficient of the x^power term
double Polynomial::coefficient(const int power) const {
    if (!head)
        return 0;
    Term *current = head;
    do {
        if (power == current->power) {
            return current->coeff;
        }
        current = current->next;
    } while (current != head);
    return 0;
}

//Returns true in == when corresponding terms of two given polynomial matches each other, otherwise false.
bool Polynomial::operator==(const Polynomial &p) const {
    if (size != p.size)
        return false;
    Term *current = head;
    do {
        if (current->coeff != p.coefficient(current->power)) {
            return false;
        }
        current = current->next;
    } while (current != head);
    return true;
}

//Returns true in != when corresponding terms of two given polynomial do not match each other, otherwise false.
bool Polynomial::operator!=(const Polynomial &p) const {
    if (size != p.size)
        return true;
    Term *current = head;
    do {
        if (current->coeff != p.coefficient(current->power)) {
            return true;
        }
        current = current->next;
    } while (current != head);
    return false;
}

//assignment operator =
Polynomial &Polynomial::operator=(const Polynomial &p) {
    Term *current = p.head;
    do {
        changeCoefficient(current->coeff, current->power);
        current = current->next;
    } while (current != p.head);
    return *this;
}

//assignment operator  +=
Polynomial &Polynomial::operator+=(const Polynomial &p) {
    Term *current = p.head;
    do {
        changeCoefficient(coefficient(current->power) + current->coeff, current->power);
        current = current->next;
    } while (current != p.head);
    return *this;
}

//assignment operator -=
Polynomial &Polynomial::operator-=(const Polynomial &p) {
    Term *current = p.head;
    do {
        changeCoefficient(coefficient(current->power) - current->coeff, current->power);
        current = current->next;
    } while (current != p.head);
    return *this;
}

//arithmetic +
Polynomial Polynomial::operator+(const Polynomial &p) const {
    Polynomial p1;
    p1 = p;
    Term *current = head;
    do {
        p1.changeCoefficient(current->coeff + p1.coefficient(current->power), current->power);
        current = current->next;
    } while (current != head);
    return p1;
}

//arithmetic -
Polynomial Polynomial::operator-(const Polynomial &p) const {
    Polynomial p1;
    p1 = p;
    Term *current = head;
    do {
        p1.changeCoefficient(current->coeff - p1.coefficient(current->power), current->power);
        current = current->next;
    } while (current != head);
    return p1;
}

// Replaces the coefficient of the x^power term with newCoeffcient.
bool Polynomial::changeCoefficient(const double newCoefficient, const int power) {
    if (!head) {
        insert(nullptr, newCoefficient, power);
        return true;
    }
    Term *current = head;
    do {
        if (power == current->power) {
            current->coeff = newCoefficient;
            return true;
        } else if (power > current->power) {
            insert(current, newCoefficient, power);
            return true;
        }
        current = current->next;
    } while (current != head);
    //insert at end
    Term *term = new Term();
    term->coeff = newCoefficient;
    term->power = power;

    head->prev->next = term;
    term->prev = head->prev;
    head->prev = term;
    term->next = head;
    size++;
    return true;
}

//inserts a new Term node with newCoefficient and power just before the existing Term pointed by the pos pointer
bool Polynomial::insert(Term *pos, const double newCoefficient, const int power) {
    Term *term = new Term();
    term->coeff = newCoefficient;
    term->power = power;
    term->next = term->prev = nullptr;
    if (!head) {
        term->next = term;
        term->prev = term;
        head = term;
        size++;
        return true;
    }
    if (head == pos && size == 1) {
        head->next = term;
        head->prev = term;
        term->next = head;
        term->prev = head;
        head = term;
        size++;
        return true;
    }
    if (head == pos) {
        head->prev->next = term;
        head->prev = term;
        term->prev = head->prev;
        term->next = head;
        head = term;
        size++;
        return true;
    }
    Term *current = head;
    while (current->next != head) {
        if (current->next == pos) {
            term->prev = current;
            term->next = current->next;
            current->next->prev = term;
            current->next = term;
            size++;
            return true;
        }
        current = current->next;
    }
    return false;
}

//deletes the existing Term node pointed by the pos pointer
bool Polynomial::remove(Term *pos) {
    Term *current = head;
    if (!head)
        return false;
    if (size == 1 && head == pos) {
        delete (head);
        head = nullptr;
        size = 0;
        return true;
    }
    if (head == pos) {
        head->prev->next = head->next;
        head->next->prev = head->prev;
        current = head;
        head = head->next;
        delete (current);
        size--;
        return true;
    }

    do {
        if (current == pos) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete (current);
            size--;
            return true;
        }
        current = current->next;
    } while (current != head);
    return false;
}

//output operator
ostream &operator<<(ostream &output, const Polynomial &p) {
    char op;
    Term *current = p.head;
    if (!current)
        return output;
    while (current->next != p.head) {
        if (current->coeff != 0) {
            if (current->coeff != 1) {
                output << current->coeff;
            }
            output << "x^" << current->power;
            if (current->next != nullptr && current->next->coeff > 0) {
                output << " + ";
            }
        } else {
            if (current->next != nullptr && current->next->coeff > 0) {
                output << " + ";
            }
        }
        current = current->next;
    };
    //last node
    if (current->coeff != 0) {
        if (current->power == 0) {
            output << current->coeff;
        } else {
            if (abs(current->coeff) != 1) {
                output << current->coeff;
            } else {
                if (current->coeff == -1) {
                    output << "-";
                }
            }
            output << "x";
            if (current->power != 1) {
                output << "^" << current->power;
            }
        }
    }
    return output;
}
//=====end of Polynomial.cpp