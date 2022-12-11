#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Vector.h"

#include <math.h>

template<typename Type>
Vector<Type>::Vector()
{
    elems_num = 0;
    alloc_data();
}

template<typename Type>
Vector<Type>::Vector(int elements_number)
{
    time_t t_time = time(NULL);
    if (elements_number < 0)
        throw VectorNegativeSizeError("elements_number < 0", __FILE__, __LINE__, ctime(&t_time));

    elems_num = elements_number;
    alloc_data();

    //for each
    for (auto &elem:*this)
        elem = 0;
    /*for (Iterator<Type> It = this->begin(); It != this->end(); ++It)
        *It = 0;*/
}

template<typename Type>
Vector<Type>::Vector(int elements_number, Type *mas)
{
    time_t t_time = time(NULL);
    if (elements_number < 0 || !mas)
        throw VectorNegativeSizeError("elements_number < 0 or/and nullptr mas", __FILE__, __LINE__, ctime(&t_time));


    elems_num = elements_number;
    alloc_data();

    int i = 0;
    /*for (Iterator<Type> It = this->begin(); It != this->end(); ++It)
        *It = vec[i++];*/
    //for each
    for (auto &elem:*this)
        elem = mas[i++];
}

template<typename Type>
Vector<Type>::Vector(int elements_number, Type vec, ...)
{
    time_t t_time = time(NULL);
    if (elements_number < 0)
        throw VectorNegativeSizeError("elements_number < 0", __FILE__, __LINE__, ctime(&t_time));

    elems_num = elements_number;
    alloc_data();

    va_list ap;
    va_start(ap, vec);
    /*for (Iterator<Type> It = this->begin(); It != this->end(); ++It)
    {
        *It = vec;
        vec = va_arg(ap, Type);
    }*/
    //for each
    for (auto &elem:*this)
    {
        elem = vec;
        vec = va_arg(ap, Type);
    }
    va_end(ap);
}

template<typename Type>
Vector<Type>::Vector(initializer_list<Type> args)
{
    if (args.size() == 0)
        Vector();

    elems_num = int(args.size());
    alloc_data();

    Iterator<Type> it = this->begin();
    for (auto &elem : args)
    {
        *it = elem;
        it++;
    }
}

template<typename Type>
Vector<Type>& Vector<Type>::operator =(initializer_list<Type> args)
{
    if (args.size() == 0)
        Vector();

    elems_num = int(args.size());
    alloc_data();

    Iterator<Type> it = this->begin();
    for (auto &elem : args)
    {
        *it = elem;
        it++;
    }
    return *this;
}

template<typename Type>
Vector<Type>::Vector(const Vector<Type> &vec)
{
    time_t t_time = time(NULL);
    if (vec.size() < 0)
        throw VectorNegativeSizeError("vec elements_number < 0", __FILE__, __LINE__, ctime(&t_time));
    elems_num = vec.size();

    alloc_data();

    for (int i = 0; i < elems_num; i++)
        data_ptr[i] = vec[i];
    //cout << "HERE copy constructor" << endl;
}

template<typename Type>
Vector<Type>& Vector<Type>::operator =(const Vector<Type> &vec)
{
    time_t t_time = time(NULL);
    //РќРµ РѕР±СЏР·Р°С‚РµР»СЊРЅРѕ, РїРѕС‚РѕРјСѓ С‡С‚Рѕ РјС‹ РЅРµ РґРѕРїСѓСЃРєР°РµРј СЃРѕР·РґР°РЅРёРµ РІРµРєС‚РѕСЂРѕРІ СЃ РѕС‚СЂРёС†Р°С‚РµР»СЊРЅС‹Рј РєРѕР»-РІРѕРј СЌР»РµРјРµРЅС‚РѕРІ
    if (vec.size() < 0)
        throw VectorNegativeSizeError("vec elements_number < 0", __FILE__, __LINE__, ctime(&t_time));
    elems_num = vec.size();

    alloc_data();

    for (int i = 0; i < elems_num; i++)
        data_ptr[i] = vec[i];
    //cout << "HERE copy operator =" << endl;
    return *this;
}

//РќСѓР¶РЅРѕ Р»Рё СЌС‚Рѕ СЂРµР°Р»РёР·РѕРІС‹РІР°С‚СЊ?
template<typename Type>
Vector<Type>::Vector(Vector<Type> &&vec) noexcept
{
    time_t t_time = time(NULL);
    if (vec.size() < 0)
        throw VectorNegativeSizeError("vec elements_number < 0", __FILE__, __LINE__, ctime(&t_time));
    elems_num = vec.size();

    data_ptr = vec.data_ptr;
    //cout << "HERE transfer constructor!!!!!!!!!!!!!!!!!" << endl;
    //vec.data_ptr.reset(); // РќРµ РѕР±СЏР·Р°С‚РµР»СЊРЅРѕ СЃ СѓРјРЅС‹РјРё СѓРєР°Р·Р°С‚РµР»СЏРјРё
}

template<typename Type>
Vector<Type>& Vector<Type>::operator =(Vector<Type> &&vec) noexcept
{
    time_t t_time = time(NULL);
    //РќРµ РѕР±СЏР·Р°С‚РµР»СЊРЅРѕ, РїРѕС‚РѕРјСѓ С‡С‚Рѕ РјС‹ РЅРµ РґРѕРїСѓСЃРєР°РµРј СЃРѕР·РґР°РЅРёРµ РІРµРєС‚РѕСЂРѕРІ СЃ РѕС‚СЂРёС†Р°С‚РµР»СЊРЅС‹Рј РєРѕР»-РІРѕРј СЌР»РµРјРµРЅС‚РѕРІ
    if (vec.size() < 0)
        throw VectorNegativeSizeError("vec elements_number < 0", __FILE__, __LINE__, ctime(&t_time));
    elems_num = vec.size();

    data_ptr = vec.data_ptr;
    //cout << "HERE transfer operator =" << endl;
    //vec.data_ptr.reset(); // РќРµ РѕР±СЏР·Р°С‚РµР»СЊРЅРѕ СЃ СѓРјРЅС‹РјРё СѓРєР°Р·Р°С‚РµР»СЏРјРё
    return *this;
}

template<typename Type>
Vector<Type>::~Vector()
{
    //data_ptr.reset();
}

template<typename Type>
bool Vector<Type>::isEmpty() const noexcept
{
    return !elems_num;
}

template<typename Type> //СЃРґРµР»Р°С‚СЊ inline?
int Vector<Type>::size() const noexcept
{
    return elems_num;
}

template<typename Type>
double Vector<Type>::len() const
{
    time_t t_time = time(NULL);
    if (isEmpty())
        throw VectorEmptyError("vector is empty", __FILE__, __LINE__, ctime(&t_time));
    double len = 0;

    Vector<double> tmp_vec(*this);
    for (auto &elem:tmp_vec)
        len += elem * elem;
    return sqrt(len);
}

template<typename Type>
bool Vector<Type>::is_zero() const
{
    return this->len() == 0;
}

template<typename Type>
bool Vector<Type>::is_unit() const
{
    return fabs(this->len() - 1) <= EPS;
}

template<typename Type>
Iterator<Type> Vector<Type>::begin() noexcept
{
    return Iterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
Iterator<Type> Vector<Type>::end() noexcept
{
    return Iterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
ConstIterator<Type> Vector<Type>::cbegin() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
ConstIterator<Type> Vector<Type>::cend() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
ConstIterator<Type> Vector<Type>::begin() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
ConstIterator<Type> Vector<Type>::end() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
Type& Vector<Type>::get_elem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw VectorIndexError("id", __FILE__, __LINE__, ctime(&t_time));
    return data_ptr[id];
}

template<typename Type>
const Type& Vector<Type>::get_elem(int id) const
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw VectorIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

template<typename Type>
Type& Vector<Type>::operator [](int id)
{
    return get_elem(id);
}

template<typename Type>
const Type& Vector<Type>::operator [](int id) const
{
    return get_elem(id);
}

template<typename Type>
void Vector<Type>::set_elem(int id, Type value)
{
    time_t t_time = time(NULL);
    if (id < 1 || id > elems_num)
        throw VectorIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    data_ptr[id] = value;
}

template<typename Type>
Vector<Type> Vector<Type>::get_unit() const
{
    time_t t_time = time(NULL);
    if (isEmpty())
        throw VectorEmptyError("vector is empty", __FILE__, __LINE__, ctime(&t_time));

    Vector<Type> unit_vector(*this);
    double length = len();
    for (auto &elem:unit_vector)
    {
        elem = elem / length;
    }
    return unit_vector;
}

template<typename Type>
Type Vector<Type>::operator *(const Vector<Type> &vec) const
{
    time_t t_time = time(NULL);
    if (isEmpty() || vec.isEmpty())
        throw VectorEmptyError("vec1 or/and vec2 is empty", __FILE__, __LINE__, ctime(&t_time));
    if (size() != vec.size())
        throw VectorDifSizeError("vec1 size != vec2 size", __FILE__, __LINE__, ctime(&t_time));

    double rez = 0;
    ConstIterator<Type> It1 = this->cbegin();
    for (ConstIterator<Type> It2 = vec.cbegin(); It1 != this->cend() || It2 != vec.cend(); It1++, It2++)
    {
        rez += (*It1) * (*It2);
    }
    return rez;
}

template<typename Type>
double Vector<Type>::get_angle(const Vector<Type> &vec) const
{
    time_t t_time = time(NULL);
    if (isEmpty() || vec.isEmpty())
        throw VectorEmptyError("vec1 or/and vec2 is empty", __FILE__, __LINE__, ctime(&t_time));
    if (size() != vec.size())
        throw VectorDifSizeError("vec1 size != vec2 size", __FILE__, __LINE__, ctime(&t_time));
    if (!this->len() || !vec.len())
        throw VectorZeroDivError("vec1 or/and vec2 len = 0", __FILE__, __LINE__, ctime(&t_time));

    double numerator = (*this) * vec;
    double denominator = (*this).len() * vec.len();
    double angle = numerator / denominator;
    angle = acos(angle) * 180 / M_PI;
    return angle;
}

template<typename Type>
double get_angle(const Vector<Type> &vec1, const Vector<Type> &vec2)
{
    return  vec1.get_angle(vec2);
}

template<typename Type>
bool Vector<Type>::is_collinear(const Vector<Type> &vec) const
{
    return get_angle(vec) < EPS;
}

template<typename Type>
bool is_collinear(const Vector<Type> &vec1, const Vector<Type> &vec2)
{
    return vec1.is_collinear(vec2);
}

template<typename Type>
bool Vector<Type>::is_orthogonal(const Vector<Type> &vec) const
{
    return abs(90 - get_angle(vec)) < EPS;
}

template<typename Type>
bool is_orthogonal(const Vector<Type> &vec1, const Vector<Type> &vec2)
{
    return vec1.is_orthogonal(vec2);
}

template<typename Type>
Vector<Type> Vector<Type>::operator +(const Type& val) const
{
    time_t t_time = time(NULL);
    if (isEmpty())
        throw VectorEmptyError("vector is empty", __FILE__, __LINE__, ctime(&t_time));

    Vector<Type> rez(*this);
    for (auto &elem:rez)
        elem += val;
    return rez;
}

template<typename Type>
Vector<Type>& Vector<Type>::operator +=(const Type& val)
{
    time_t t_time = time(NULL);
    if (isEmpty())
        throw VectorEmptyError("vector is empty", __FILE__, __LINE__, ctime(&t_time));

    for (auto &elem:*this)
        elem += val;
    return *this;
}

template<typename Type>
Vector<Type> Vector<Type>::scalar_add(const Type &val)
{
    Vector<Type> rez = *this + val;
    *this = Vector<Type>(rez);
    return rez;
}

template<typename Type>
Vector<Type> Vector<Type>::operator +(const Vector<Type> &vec) const
{
    time_t t_time = time(NULL);
    if (isEmpty() || vec.isEmpty())
        throw VectorEmptyError("vec1 or/and vec2 is empty", __FILE__, __LINE__, ctime(&t_time));
    if (size() != vec.size())
        throw VectorDifSizeError("vec1 size != vec2 size", __FILE__, __LINE__, ctime(&t_time));

    Vector<Type> rez(elems_num);
    int i = 0;
    ConstIterator<Type> It1 = this->cbegin();
    for (ConstIterator<Type> It2 = vec.cbegin(); It1 != this->cend() || It2 != vec.cend(); It1++, It2++)
    {
        rez[i++] = (*It1) + (*It2);
    }
    return rez;
}

template<typename Type>
Vector<Type>& Vector<Type>::operator +=(const Vector<Type> &vec)
{
    Vector<Type> sum_vec = *this + vec;
    *this = Vector<Type>(sum_vec);
    return *this;
}

template<typename Type>
Vector<Type> Vector<Type>::vector_add(const Vector<Type> &vec)
{
    Vector<Type> rez = *this + vec;
    *this = Vector<Type>(rez);
    return rez;
}

template<typename Type>
Vector<Type> Vector<Type>::operator -(const Type& val) const
{
    time_t t_time = time(NULL);
    if (isEmpty())
        throw VectorEmptyError("vec is empty", __FILE__, __LINE__, ctime(&t_time));

    Vector<Type> rez(*this);
    for (auto &elem:rez)
        elem -= val;
    return rez;
}

template<typename Type>
Vector<Type>& Vector<Type>::operator -=(const Type& val)
{
    time_t t_time = time(NULL);
    if (isEmpty())
        throw VectorEmptyError("vec is empty", __FILE__, __LINE__, ctime(&t_time));

    for (auto &elem:*this)
        elem -= val;
    return *this;
}

template<typename Type>
Vector<Type> Vector<Type>::scalar_dif(const Type &val)
{
    Vector<Type> rez = *this - val;
    *this = Vector<Type>(rez);
    return rez;
}

template<typename Type>
Vector<Type> Vector<Type>::operator -(const Vector<Type> &vec) const
{
    time_t t_time = time(NULL);
    if (isEmpty() || vec.isEmpty())
        throw VectorEmptyError("vec1 or/and vec2 is empty", __FILE__, __LINE__, ctime(&t_time));
    if (size() != vec.size())
        throw VectorDifSizeError("vec1 size != vec2 size", __FILE__, __LINE__, ctime(&t_time));

    Vector<Type> rez(elems_num);
    int i = 0;
    ConstIterator<Type> It1 = this->cbegin();
    for (ConstIterator<Type> It2 = vec.cbegin(); It1 != this->cend() || It2 != vec.cend(); It1++, It2++)
    {
        rez[i++] = (*It1) - (*It2);
    }
    return rez;
}

template<typename Type>
Vector<Type>& Vector<Type>::operator -=(const Vector<Type> &vec)
{
    Vector<Type> sum_vec = *this - vec;
    *this = Vector<Type>(sum_vec);
    return *this;
}

template<typename Type>
Vector<Type> Vector<Type>::vector_dif(const Vector<Type>& vec)
{
    Vector<Type> rez = *this - vec;
    *this = Vector<Type>(rez);
    return rez;
}

template<typename Type>
Vector<Type> Vector<Type>::operator *(const Type& val)
{
    time_t t_time = time(NULL);
    if (isEmpty())
        throw VectorEmptyError("vec is empty", __FILE__, __LINE__, ctime(&t_time));

    Vector<Type> rez(*this);
    for (auto &elem:rez)
        elem = elem * val;
    return rez;
}

template<typename Type>
Vector<Type>& Vector<Type>::operator *=(const Type& val)
{
    Vector<Type> mul_vec = *this * val;
    *this = Vector<Type>(mul_vec);
    return *this;
}

template<typename Type>
Vector<Type> Vector<Type>::scalar_mul(const Type &val)
{
    Vector<Type> rez = *this * val;
    *this = Vector<Type>(rez);
    return rez;
}

template<typename Type>
Vector<Type> Vector<Type>::operator /(const Type& val)
{
    time_t t_time = time(NULL);
    if (isEmpty())
        throw VectorEmptyError("vec is empty", __FILE__, __LINE__, ctime(&t_time));

    Vector<Type> rez(*this);
    for (auto &elem:rez)
        elem = elem / val;
    return rez;
}

template<typename Type>
Vector<Type>& Vector<Type>::operator /=(const Type& val)
{
    Vector<Type> div_vec = *this / val;
    *this = Vector<Type>(div_vec);
    return *this;
}

template<typename Type>
Vector<Type> Vector<Type>::scalar_div(const Type &val)
{
    Vector<Type> rez = *this / val;
    *this = Vector<Type>(rez);
    return rez;
}

template<typename Type>
Vector<Type> Vector<Type>::operator &(const Vector<Type> &vec) const
{
    time_t t_time = time(NULL);
    if (isEmpty() || vec.isEmpty())
        throw VectorEmptyError("vec1 or/and vec2 is empty", __FILE__, __LINE__, ctime(&t_time));
    if (size() != vec.size())
        throw VectorDifSizeError("vec1 size != vec2 size", __FILE__, __LINE__, ctime(&t_time));
    if (size() != 2 && size() != 3)
        throw VectorSizeError("vec is not 2D or 3D", __FILE__, __LINE__, ctime(&t_time));

    Type x = 0, y = 0, z = 0;
    if (size() == 3)
    {
        x = (*this)[1] * vec[2] - (*this)[2] * vec[1];
        y = (*this)[2] * vec[0] - (*this)[0] * vec[2];
        z = (*this)[0] * vec[1] - (*this)[1] * vec[0];

        Vector<Type> rez_vec{x, y, z};
        return rez_vec;
    }
    else if (size() == 2)
    {
        z = (*this)[0] * vec[1] - (*this)[1] * vec[0];

        Vector<Type> rez_vec{x, y, z};
        return rez_vec;
    }
    //return nullptr; // ??? shouldn't be here
}

template<typename Type>
Vector<Type>& Vector<Type>::operator &=(const Vector<Type> &vec)
{
    Vector<Type> mult_vec = *this & vec;

    time_t t_time = time(NULL);
    if (size() != 2 && size() != 3)
        throw VectorSizeError("vec is not 2D or 3D", __FILE__, __LINE__, ctime(&t_time));

    *this = Vector<Type>(mult_vec);
    return *this;
}

template<typename Type>
Vector<Type> Vector<Type>::vector_mul(const Vector<Type>& vec)
{
    Vector<Type> rez = *this & vec;
    *this = Vector<Type>(rez);
    return rez;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::operator *(const Vector<Type2> &vec) const //decltype(auto)
{
    time_t t_time = time(NULL);
    if (isEmpty() || vec.isEmpty())
        throw VectorEmptyError("vec1 or/and vec2 is empty", __FILE__, __LINE__, ctime(&t_time));
    if (size() != vec.size())
        throw VectorDifSizeError("vec1 size != vec2 size", __FILE__, __LINE__, ctime(&t_time));

    Vector<decltype((*this)[0] * vec[0])> rez(elems_num);
    int i = 0;
    ConstIterator<Type> It1 = this->cbegin();
    for (ConstIterator<Type2> It2 = vec.cbegin(); It1 != this->cend() || It2 != vec.cend(); It1++, It2++)
    {
        rez[i++] = (*It1) * (*It2);
    }
    return rez;
}

template<typename Type>
template<typename Type2>
Vector<Type>& Vector<Type>::operator *=(const Vector<Type2>& vec)
{
    time_t t_time = time(NULL);
    if (isEmpty() || vec.isEmpty())
        throw VectorEmptyError("vec1 or/and vec2 is empty", __FILE__, __LINE__, ctime(&t_time));
    if (size() != vec.size())
        throw VectorDifSizeError("vec1 size != vec2 size", __FILE__, __LINE__, ctime(&t_time));

    Vector<Type> rez(elems_num);
    int i = 0;
    ConstIterator<Type> It1 = this->cbegin();
    for (ConstIterator<Type2> It2 = vec.cbegin(); It1 != this->cend() || It2 != vec.cend(); It1++, It2++)
    {
        rez[i++] = (*It1) * (*It2);
    }
    *this = Vector<Type>(rez);
    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> Vector<Type>::elems_mul(const Vector<Type2>& vec)
{
    Vector<Type> rez = *this * vec;
    *this = Vector<Type>(rez);
    return rez;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::operator +(const Vector<Type2>& vec) const
{
    time_t t_time = time(NULL);
    if (isEmpty() || vec.isEmpty())
        throw VectorEmptyError("vec1 or/and vec2 is empty", __FILE__, __LINE__, ctime(&t_time));
    if (size() != vec.size())
        throw VectorDifSizeError("vec1 size != vec2 size", __FILE__, __LINE__, ctime(&t_time));

    //Vector<Type> rez(elems_num);
    Vector<decltype((*this)[0] + vec[0])> rez(elems_num);
    int i = 0;
    ConstIterator<Type> It1 = this->cbegin();
    for (ConstIterator<Type2> It2 = vec.cbegin(); It1 != this->cend() || It2 != vec.cend(); It1++, It2++)
    {
        rez[i++] = (*It1) + (*It2);
    }
    return rez;
}

template<typename Type>
template<typename Type2>
Vector<Type>& Vector<Type>::operator +=(const Vector<Type2>& vec)
{
    time_t t_time = time(NULL);
    if (isEmpty() || vec.isEmpty())
        throw VectorEmptyError("vec1 or/and vec2 is empty", __FILE__, __LINE__, ctime(&t_time));
    if (size() != vec.size())
        throw VectorDifSizeError("vec1 size != vec2 size", __FILE__, __LINE__, ctime(&t_time));

    //Vector<Type> rez(elems_num);
    Vector<Type> rez(elems_num);
    int i = 0;
    ConstIterator<Type> It1 = this->cbegin();
    for (ConstIterator<Type2> It2 = vec.cbegin(); It1 != this->cend() || It2 != vec.cend(); It1++, It2++)
    {
        rez[i++] = (*It1) + (*It2);
    }
    *this = Vector<Type>(rez);
    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> Vector<Type>::elems_add(const Vector<Type2>& vec)
{
    Vector<Type> rez = *this + vec;
    *this = Vector<Type>(rez);
    return rez;
}

template<typename Type>
void Vector<Type>::alloc_data()
{
    data_ptr.reset();
    if (elems_num != 0)
    {
        shared_ptr<Type[]> new_ptr(new Type[elems_num]);

        time_t t_time = time(NULL);
        if (!new_ptr)
            throw VectorMemoryError("allocationg data_ptr error", __FILE__, __LINE__, ctime(&t_time));

        data_ptr = new_ptr;
    }
}

template<typename Type>
ostream& operator <<(ostream& os, const Vector<Type>& vec)
{
    if (vec.isEmpty())
    {
        os << "Vector is empty.";
        return os;
    }

    ConstIterator<Type> It = vec.cbegin();
    os << '(' << *It++;
    for (; It != vec.cend(); It++)
        os << ", " << *It ;
    os << ')';

    return os;
}

#endif // VECTOR_HPP
