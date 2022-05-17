#ifndef ITERATOR_H
#define ITERATOR_H

#include "BaseIterator.hpp"

using namespace std;

template<typename Type>
class Iterator:public BaseIterator<Type>
{
public:
    Iterator();
    virtual ~Iterator() = default;
    Iterator(const Iterator<Type>& it); //copy

    explicit Iterator(shared_ptr<Type[]> ptr, int num, int index = 0); //init

    Type& operator *();

    Type& operator [](int index);

    Type* operator ->();
};

#endif // ITERATOR_H
