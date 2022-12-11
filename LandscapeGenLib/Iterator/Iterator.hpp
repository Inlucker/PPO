#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "Iterator.h"

template<typename Type>
Iterator<Type>::Iterator() //: BaseIterator<Type>()
{
}

template<typename Type>
Iterator<Type>::Iterator(const Iterator<Type> &it) : BaseIterator<Type>(it)
{
}

template<typename Type>
Iterator<Type>::Iterator(shared_ptr<Type[]> ptr, int num, int index) : BaseIterator<Type>(ptr, num, index)
{
}


template<typename Type>
Type& Iterator<Type>::operator *()
{
    this->check_ptr(__LINE__);

    time_t t_time = time(NULL);
    if (this->id < 0 || this->id >= this->elems_num)
        throw IteratorIdError("id", __FILE__, __LINE__, ctime(&t_time));

    return this->cur_elem();
}

template<typename Type>
Type &Iterator<Type>::operator [](int index)
{
    this->check_ptr(__LINE__);

    time_t t_time = time(NULL);
    if (this->id + index < 0 || this->id + index >= this->elems_num)
        throw IteratorIdError("index", __FILE__, __LINE__, ctime(&t_time));

    Iterator<Type> tmp(*this);
    tmp += index;
    return *tmp;
}

template<typename Type>
Type *Iterator<Type>::operator ->()
{
    this->check_ptr(__LINE__);

    time_t t_time = time(NULL);
    if (this->id < 0 || this->id >= this->elems_num)
        throw IteratorIdError("id", __FILE__, __LINE__, ctime(&t_time));

    return &(this->cur_elem());
}

#endif // ITERATOR_HPP
