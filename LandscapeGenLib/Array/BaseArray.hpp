#ifndef BASEARRAY_HPP
#define BASEARRAY_HPP

#include "BaseArray.h"

template<typename Type>
BaseArray<Type>::BaseArray()
{
    elems_num = 0;
    alloc_data();
}

template<typename Type>
BaseArray<Type>::BaseArray(int new_size)
{
    time_t t_time = time(NULL);
    if (new_size < 0)
        throw ArrayNegativeSizeError("new_size < 0", __FILE__, __LINE__, ctime(&t_time));

    if (new_size == 0)
    {
        elems_num = 0;
        data_ptr.reset();
    }
    else
    {
        elems_num = new_size;
        alloc_data();

        for (auto &elem:*this)
            elem = Type();
    }
}

template<typename Type>
bool BaseArray<Type>::isEmpty() const noexcept
{
    return !elems_num;
}

template<typename Type>
int BaseArray<Type>::size() const noexcept
{
    return elems_num;
}

template<typename Type>
int BaseArray<Type>::elemsNum() const noexcept
{
    return elems_num;
}

template<typename Type>
Iterator<Type> BaseArray<Type>::begin() noexcept
{
    return Iterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
Iterator<Type> BaseArray<Type>::end() noexcept
{
    return Iterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
ConstIterator<Type> BaseArray<Type>::cbegin() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
ConstIterator<Type> BaseArray<Type>::cend() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
ConstIterator<Type> BaseArray<Type>::begin() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
ConstIterator<Type> BaseArray<Type>::end() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
Type &BaseArray<Type>::getElem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw ArrayIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

template<typename Type>
const Type &BaseArray<Type>::getElem(int id) const
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw ArrayIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

template<typename Type>
Type &BaseArray<Type>::operator [](int id)
{
    return getElem(id);
}

template<typename Type>
const Type &BaseArray<Type>::operator [](int id) const
{
    return getElem(id);
}

template<typename Type>
bool BaseArray<Type>::operator ==(BaseArray<Type> &an_array) const
{
    if (this->size() != an_array.size())
        return false;

    for (int i = 0; i < elems_num; i++)
        if ((*this)[i] != an_array[i])
            return false;

    return true;
}

template<typename Type>
bool BaseArray<Type>::operator !=(BaseArray<Type> &an_array) const
{
    return !(*this == an_array);
}

template<typename Type>
void BaseArray<Type>::alloc_data()
{
    data_ptr.reset();
    if (elems_num != 0)
    {
        shared_ptr<Type[]> new_ptr(new Type[elems_num]);

        time_t t_time = time(NULL);
        if (!new_ptr)
            throw ArrayAllocError("Allocationg data_ptr error", __FILE__, __LINE__, ctime(&t_time));

        data_ptr = new_ptr;
    }
}

#endif // BASEARRAY_HPP
