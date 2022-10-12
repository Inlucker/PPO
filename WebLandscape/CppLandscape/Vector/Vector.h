#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <cmath>
#include <stdarg.h>
#include <iostream>
#include <time.h>

#include "AbstractVector.h"
#include "../Iterator/Iterator.hpp"
#include "../Iterator/ConstIterator.hpp"
#include "../Errors/VectorErrors.h"

#ifndef EPS
#define EPS 1e-06
#endif

using namespace std;

template<typename Type>
class Vector : public AbstractVector
{
public:
    Vector();
    explicit  Vector(int elements_number);
    Vector(int elements_number, Type* mas);
    Vector(int elements_number, Type vec, ...);
    Vector(initializer_list<Type> args);
    Vector<Type>& operator =(initializer_list<Type> args);

    explicit Vector(const Vector<Type>& vec); //copy
    Vector<Type>& operator =(const Vector<Type>& vec);
    Vector(Vector<Type>&& vec) noexcept; //РџРµСЂРµРЅРµРѕСЃ
    Vector<Type>& operator =(Vector<Type>&& vec) noexcept;

    ~Vector();

    bool isEmpty() const noexcept;
    int size() const noexcept;

    Iterator<Type> begin() noexcept;
    Iterator<Type> end() noexcept;
    ConstIterator<Type> cbegin() const noexcept;
    ConstIterator<Type> cend() const noexcept;
    ConstIterator<Type> begin() const noexcept;
    ConstIterator<Type> end() const noexcept;

    Type& get_elem(int id);
    const Type& get_elem(int id) const;
    Type& operator [](int id);
    const Type& operator [](int id) const;
    void set_elem(int id, Type value);

    //Math
    double len() const;
    bool is_zero() const;
    bool is_unit() const;
    Vector<Type> get_unit() const;
    Type operator *(const Vector<Type>& vec) const;
    double get_angle(const Vector<Type>& vec2) const;
    bool is_collinear(const Vector<Type>& vec) const;
    bool is_orthogonal(const Vector<Type>& vec) const;

    Vector<Type> operator +(const Type& val) const;
    Vector<Type>& operator +=(const Type& val);
    Vector<Type> scalar_add(const Type& val);

    Vector<Type> operator +(const Vector<Type>& vec) const;
    Vector<Type>& operator +=(const Vector<Type>& vec);
    Vector<Type> vector_add(const Vector<Type>& vec);

    Vector<Type> operator -(const Type& val) const;
    Vector<Type>& operator -=(const Type& val);
    Vector<Type> scalar_dif(const Type& val);

    Vector<Type> operator -(const Vector<Type>& vec) const;
    Vector<Type>& operator -=(const Vector<Type>& vec);
    Vector<Type> vector_dif(const Vector<Type>& vec);

    Vector<Type> operator *(const Type& val);
    Vector<Type>& operator *=(const Type& val);
    Vector<Type> scalar_mul(const Type& val);

    Vector<Type> operator /(const Type& val);
    Vector<Type>& operator /=(const Type& val);
    Vector<Type> scalar_div(const Type& val);

    Vector<Type> operator &(const Vector<Type>& vec) const;
    Vector<Type>& operator &=(const Vector<Type>& vec);
    Vector<Type> vector_mul(const Vector<Type>& vec);

    template<typename Type2>
    decltype(auto) operator *(const Vector<Type2>& vec) const;
    template<typename Type2>
    Vector<Type>& operator *=(const Vector<Type2>& vec);
    template<typename Type2>
    Vector<Type> elems_mul(const Vector<Type2>& vec);

    template<typename Type2>
    decltype(auto) operator +(const Vector<Type2>& vec) const;
    template<typename Type2>
    Vector<Type>& operator +=(const Vector<Type2>& vec);
    template<typename Type2>
    Vector<Type> elems_add(const Vector<Type2>& vec);

private:
    shared_ptr<Type[]> data_ptr;

protected:
    void alloc_data();
};

#endif // VECTOR_H
