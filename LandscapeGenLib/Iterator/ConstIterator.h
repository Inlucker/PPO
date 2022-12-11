#ifndef CONSTITERATOR_H
#define CONSTITERATOR_H

#include "BaseIterator.hpp"

using namespace std;

template<class Type>
class Vector;

template<typename Type>
class ConstIterator:public BaseIterator<Type>
{
public:
    ConstIterator();
    virtual ~ConstIterator() = default;
    ConstIterator(const ConstIterator<Type>& it); //copy

    explicit ConstIterator(shared_ptr<Type[]> ptr, int num, int index = 0); //init

protected:
};

#endif // CONSTITERATOR_H
