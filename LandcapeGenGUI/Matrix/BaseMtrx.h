#ifndef BASEMTRX_H
#define BASEMTRX_H

#include <memory>
#include <iostream>
#include <time.h>

using namespace std;

#include "AbstractMtrx.h"
#include "Iterator/Iterator.hpp"
#include "Iterator/ConstIterator.hpp"
#include "Errors/MtrxErrors.h"

#ifndef EPS
#define EPS 1e-06
#endif

template<typename Type>
class BaseMtrx : public AbstractMtrx
{
public:
    BaseMtrx();
    explicit BaseMtrx(int new_size);
    BaseMtrx(int new_width, int new_height);

    virtual ~BaseMtrx() = default;

    //virtual bool isEmpty() const noexcept;
    //virtual int getSize() const noexcept;
    //virtual int elemsNum() const noexcept;
    virtual void reset() noexcept;

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

    //Done instead of operator[][]
    Type& getElem(int i, int j);
    const Type& getElem(int i, int j) const;
    Type& operator()(int i, int j);
    const Type& operator()(const int &i, const int &j) const;

    //bool operator ==(BaseMtrx<double>& an_mtrx);
    bool operator ==(const BaseMtrx<Type>& an_mtrx);
    bool operator !=(const BaseMtrx<Type>& an_mtrx);

protected:
    virtual void alloc_data();

protected:
    shared_ptr<Type[]> data_ptr;
};

#endif // BASEMTRX_H
