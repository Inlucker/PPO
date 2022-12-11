#ifndef BASEITERATOR_H
#define BASEITERATOR_H
#include <memory>
#include <time.h>
#include <iostream>

#include "AbstractIterator.h"

using namespace std;

template<typename Type>
class BaseIterator:public AbstractIterator
{
public:
    BaseIterator();
    virtual ~BaseIterator() = default;
    BaseIterator(const BaseIterator<Type>& it); //copy
    BaseIterator<Type>& operator =(const BaseIterator<Type>& it);

    explicit BaseIterator(shared_ptr<Type[]> ptr, int num, int index = 0); //init

    int get_id() const;
    int get_els_num() const;

    bool operator ==(const BaseIterator<Type>& it) const;
    bool operator !=(const BaseIterator<Type>& it) const;
    operator bool() const;

    BaseIterator<Type> &operator ++(); //++it
    BaseIterator<Type> operator ++(int); //it++

    //--, +=, -=, +, -, -It, [], <, >, <=, >=

    BaseIterator<Type> &operator --(); //++it
    BaseIterator<Type> operator --(int); //it++

    BaseIterator<Type>& operator +=(int n);
    BaseIterator<Type> operator +(int n) const;
    BaseIterator<Type>& operator -=(int n);
    BaseIterator<Type> operator -(int n) const;

    int operator -(const BaseIterator<Type>& it) const;

    const Type& operator *() const;
    const Type& operator [](int index) const;
    const Type* operator ->() const;

    bool operator <(const BaseIterator<Type>& it) const;
    bool operator <=(const BaseIterator<Type>& it) const;
    bool operator >(const BaseIterator<Type>& it) const;
    bool operator >=(const BaseIterator<Type>& it) const;

protected:
    weak_ptr<Type[]> data_ptr;
    bool check_ptr(int line) const;
    Type& cur_elem() const;
};

#endif // BASEITERATOR_H
