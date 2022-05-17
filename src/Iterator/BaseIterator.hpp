#ifndef BASEITERATOR_HPP
#define BASEITERATOR_HPP

#include "BaseIterator.h"
#include "Errors/IteratorErrors.h"

template<typename Type>
BaseIterator<Type>::BaseIterator()
{
    id = 0;
    elems_num = 0;
}

template<typename Type>
BaseIterator<Type>::BaseIterator(const BaseIterator<Type> &it)
{
    id = it.id;
    elems_num = it.elems_num;
    data_ptr = it.data_ptr;
}

template<typename Type>
BaseIterator<Type> &BaseIterator<Type>::operator =(const BaseIterator<Type> &it)
{
    id = it.id;
    elems_num = it.elems_num;
    data_ptr = it.data_ptr;
    return *this;
}

template<typename Type>
BaseIterator<Type>::BaseIterator(shared_ptr<Type[]> ptr, int num, int index)
{
    id = index;
    elems_num = num;
    data_ptr = ptr;
}

template<typename Type>
int BaseIterator<Type>::get_id() const
{
    return id;
}

template<typename Type>
int BaseIterator<Type>::get_els_num() const
{
    return elems_num;
}

template<typename Type>
bool BaseIterator<Type>::operator ==(const BaseIterator<Type> &it) const
{
   // check_ptr(__LINE__);

    return !(id != it.id || data_ptr.lock() != it.data_ptr.lock());
}

template<typename Type>
bool BaseIterator<Type>::operator !=(const BaseIterator<Type> &it) const
{
    //check_ptr(__LINE__);

    return id != it.id || data_ptr.lock() != it.data_ptr.lock();
}

template<typename Type>
BaseIterator<Type>::operator bool() const
{
    //check_ptr(__LINE__);

    return (id >= 0 && id < elems_num && elems_num > 0);
}

template<typename Type>
BaseIterator<Type> &BaseIterator<Type>::operator ++() //++it
{
    check_ptr(__LINE__);

    id++;
    return *this;
}

template<typename Type>
BaseIterator<Type> BaseIterator<Type>::operator ++(int) //it++
{
    check_ptr(__LINE__);

    BaseIterator<Type> tmp(*this);
    ++(*this); //id++;
    return tmp;
}

template<typename Type>
BaseIterator<Type> &BaseIterator<Type>::operator --()
{
    check_ptr(__LINE__);

    id--;
    return *this;
}

template<typename Type>
BaseIterator<Type> BaseIterator<Type>::operator --(int)
{
    check_ptr(__LINE__);

    BaseIterator<Type> tmp(*this);
    --(*this); //id--;
    return tmp;
}

template<class Type>
BaseIterator<Type>& BaseIterator<Type>::operator +=(int n)
{
    check_ptr(__LINE__);

    id += n;
    return *this;
}

template<class Type>
BaseIterator<Type> BaseIterator<Type>::operator +(int n) const
{
    check_ptr(__LINE__);

    BaseIterator<Type> sum_it(*this);
    sum_it += n;
    return sum_it;
}

template<class Type>
BaseIterator<Type>& BaseIterator<Type>::operator -=(int n)
{
    check_ptr(__LINE__);

    id -= n;
    return *this;
}

template<class Type>
BaseIterator<Type> BaseIterator<Type>::operator -(int n) const
{
    check_ptr(__LINE__);

    BaseIterator<Type> dif_it(*this);
    dif_it -= n;
    return dif_it;
}

template<class Type>
int BaseIterator<Type>::operator -(const BaseIterator<Type>& it) const
{
    check_ptr(__LINE__);

    int dif = id - it.id;
    return dif;
}

template<class Type>
const Type& BaseIterator<Type>::operator *() const
{
    this->check_ptr(__LINE__);

    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw IteratorIdError("id", __FILE__, __LINE__, ctime(&t_time));

    return this->cur_elem();
}

template<typename Type>
const Type &BaseIterator<Type>::operator [](int index) const
{
    this->check_ptr(__LINE__);

    time_t t_time = time(NULL);
    if (id + index < 0 || id + index >= elems_num)
        throw IteratorIdError("index", __FILE__, __LINE__, ctime(&t_time));

    BaseIterator<Type> tmp(*this);
    tmp += index;
    return *tmp;
}

template<typename Type>
const Type *BaseIterator<Type>::operator ->() const
{
    check_ptr(__LINE__);

    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw IteratorIdError("id", __FILE__, __LINE__, ctime(&t_time));

    return &(this->cur_elem());
}

template<typename Type>
bool BaseIterator<Type>::operator <(const BaseIterator<Type> &it) const
{
    return id < it.id;
}

template<typename Type>
bool BaseIterator<Type>::operator <=(const BaseIterator<Type> &it) const
{
    return id <= it.id;
}

template<typename Type>
bool BaseIterator<Type>::operator >(const BaseIterator<Type> &it) const
{
    return id > it.id;
}

template<typename Type>
bool BaseIterator<Type>::operator >=(const BaseIterator<Type> &it) const
{
    return id >= it.id;
}

template<typename Type>
bool BaseIterator<Type>::check_ptr(int line) const
{
    if (!data_ptr.expired())
        return true;

    time_t t_time = time(NULL);
    throw IteratorWeakPtrError("Iterator with no ptr", __FILE__, line, ctime(&t_time));
    return false;
}

template<typename Type>
Type &BaseIterator<Type>::cur_elem() const
{
    shared_ptr<Type[]> copy_ptr = data_ptr.lock();
    return (copy_ptr[id]);
}

#endif // BASEITERATOR_HPP
