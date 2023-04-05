//
//  main.cpp
//  polynomial
//
//  Created by Arash Dewan on 4/5/23.
//

#include <iostream>
#include<sstream>
#include<iomanip>
#include <string>
#include <ctime>
#include <vector>
#include<fstream>
#include<numeric>
#include <cwchar>
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
//term constructor
Term::Term(double c, int p) {
    coef = c;
    pow = p;
    next = nullptr;
    previous = nullptr;
}
void Iterator::next() {
    if (position == container->last)
    {
        position = nullptr;
    }
    else {
        position = position->next;
    }
}
void Iterator::previous() {
    if (position == nullptr) {
        position = container->last;
    }
    else {
        position = position->previous;
    }
}
bool Iterator::equals(Iterator const& other) {
    return (position == other.position);
}
Polynomial::Polynomial(Term a) {
    push_back(a);
}
Iterator Polynomial::begin() {
    Iterator iter;
    iter.position = first;
    iter.container = this;
    return iter;
}
Iterator Polynomial::end() {
    Iterator iter;
    iter.position = nullptr;
    iter.container = this;
    return iter;
}
void Polynomial::add(Term new_term) {
    if (new_term.coef == 0)
    {//if the coef is zero, we don't need to add it into the list
        return;
    }
    Iterator pos;
    Iterator polyend = end();
    for (pos = begin(); !pos.equals(polyend); pos.next())
    {
        if (new_term.pow == pos.position->pow) {
            // if there is such a term in the list, then update the coef
            int temp = pos.position->coef + new_term.coef;
            if (temp == 0)
            {//delete the term if the resulting coef is zero
                erase(pos);
            }
            else
            {//update the coef
                pos.position->coef = temp;
            }
            return;
        }
    }
//if there is no such a term in the list, then add it in the list
    this->push_back(new_term);
}
void Polynomial::push_back(const Term& c) {
    Term* new_term = new Term(c.coef, c.pow);
    if (last == nullptr) // List is empty
    {
        first = new_term;
        last = new_term;
    }
    else
    {
        new_term->previous = last;
        last->next = new_term;
        last = new_term;
    }
}
void Polynomial::insert(Iterator& iter, Term c) {
    if (iter.position == nullptr) {
        push_back(c);
        return;
    }
    Term* after = iter.position;
    Term* before = after->previous;
    Term* new_term = &c;
    new_term->previous = before;
    new_term->next = after;
    after->previous = new_term;
    if (before == nullptr) { // Insert at beginning
        first = new_term;
    }
    else {
        before->next = new_term;
    }
}
Iterator Polynomial::erase(Iterator iter) {
    Term* remove = iter.position;
    Term* before = remove->previous;
    Term* after = remove->next;
    if (remove == first)
    {
        first = after;
    }
    else
    {
        before->next = after;
    }
    if (remove == last)
    {
        last = before;
    }
    else
    {
        after->previous = before;
    }
    delete remove;
    Iterator r;
    r.position = after;
    r.container = this;
    return r;
}
void Polynomial::print() {
    Iterator pos = begin();
    if (pos.position == nullptr) {
        return;//empty list
}
//Since the list is not empty, we can display the first element in the list
    cout << *(pos.position);
    pos.next();
    Iterator polyend = end();
    while (!pos.equals(polyend)) {
        if (pos.position->coef > 0) {
            cout << "+";//we don't need to display the plus sign, if coef is negative
        }
        cout << *(pos.position);
        pos.next();
    }
    cout << endl;
    }
Polynomial Polynomial::addition(Polynomial other) {
    Polynomial sum;//New polynomial
    //add terms from "this" polynomial
    for (Iterator pos = begin(); pos.position != nullptr; pos.next()) {
        sum.push_back(Term(pos.position->coef, pos.position->pow));
    }
    //add terms from "other" polynomial
    for (Iterator pos = other.begin(); pos.position != nullptr; pos.next()) {
        sum.add(Term(pos.position->coef, pos.position->pow));
    }
    return sum;
}

int main() {
    Polynomial p(Term(-2, 0));//p=-2
    p.add(Term(1, 1));//p=x-2
    p.add(Term(2, 2));//p=2*x^2+x-2
    p.print();
    Polynomial q(Term(2, 0));//q=2
    q.add(Term(-1, 1));//q=-x+2
    q.add(Term(1, 3));//q=x^3-x+2
    q.print();
    Polynomial h = p.addition(p);
    h.print();
    h = p.addition(q);
    h.print();
    return 0;
}
