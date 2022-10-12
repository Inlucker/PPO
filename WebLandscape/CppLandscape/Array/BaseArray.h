#ifndef BASEARRAY_H
#define BASEARRAY_H

#include <memory>
#include <iostream>
#include <time.h>

using namespace std;

#include "AbstractArray.h"
#include "../Iterator/Iterator.hpp"
#include "../Iterator/ConstIterator.hpp"
#include "../Errors/ArrayErrors.h"

template<typename Type>
class BaseArray : public AbstractArray
{
public:
    BaseArray();
    explicit BaseArray(int new_size);

    virtual ~BaseArray() = default;

    virtual bool isEmpty() const noexcept;
    virtual int size() const noexcept;
    virtual int elemsNum() const noexcept;

    Iterator<Type> begin() noexcept;
    Iterator<Type> end() noexcept;
    ConstIterator<Type> cbegin() const noexcept;
    ConstIterator<Type> cend() const noexcept;
    ConstIterator<Type> begin() const noexcept;
    ConstIterator<Type> end() const noexcept;

    Type& getElem(int id);
    const Type& getElem(int id) const;
    Type& operator [](int id);
    const Type& operator [](int id) const;

protected:
    virtual void alloc_data();

protected:
    shared_ptr<Type[]> data_ptr;
};

#endif // BASEARRAY_H
