//
//  Header.h
//  polynomial
//
//  Created by Arash Dewan on 4/5/23.
//

#ifndef Header_h
#define Header_h
#include <iostream>
#include<sstream>
#include<iomanip>
#include <string>
#include <vector>
#include<fstream>

using namespace std;

//declarations
class Polynomial;
class Term;
class Iterator;
//definitions
class Polynomial {
public:
    Polynomial() { first = nullptr;last = nullptr; };
    Polynomial(Term a);
    void add(Term b);
    Polynomial addition(Polynomial a);
    void print();
    Iterator begin();
    Iterator end();
    void push_back(const Term& c);
    void insert(Iterator& iter, Term c);
    Iterator erase(Iterator iter);
private:
    Term* first;
    Term* last;
    friend class Iterator;
};
class Term {
public:
    Term() { coef = 0;pow = 0; };
    Term(double c, int p);
private:
    double coef;
    int pow;
    Term* previous;
    Term* next;
    friend class Polynomial;
    friend class Iterator;
    friend ostream& operator<<(ostream& out, const Term& para);
};
ostream& operator<<(ostream& out, const Term& para) {
    if (para.pow == 0)
    {
        out << para.coef;
        return out;
    }
    if (para.coef == 1)
    {
        if (para.pow == 1)
        {
            out << "x";
            return out;
        }
        else
        {
            out << "x^" << para.pow;
            return out;
        }
    }
    else if (para.coef == -1)
    {
        if (para.pow == 1)
        {
            out << "-x";
            return out;
        }
        else
        {
            out << "-x^" << para.pow;
            return out;
        }
    }
    else
    {
        out << para.coef;
    }
    if (para.pow == 1)
    {
        out << "*x";
    }
    else
    {
        out << "*x^" << para.pow;
    }
    return out;
}
class Iterator {
public:
    Iterator() :position(nullptr), container(nullptr) {};
    void next();
    void previous();
    bool equals(Iterator const& other);
    double get_coef() { return position->coef; };
    int get_pow() { return position->pow; };
private:
    Term* position;
    Polynomial* container;
    friend class Polynomial;
};

#endif /* Header_h */
