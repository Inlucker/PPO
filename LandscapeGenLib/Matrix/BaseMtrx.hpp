#ifndef BASEMTRX_HPP
#define BASEMTRX_HPP

#include "BaseMtrx.h"

template<typename Type>
BaseMtrx<Type>::BaseMtrx()
{
    //size = 0;
    //elems_num = 0;
    alloc_data();
}

template<typename Type>
BaseMtrx<Type>::BaseMtrx(int new_size)
{
    time_t t_time = time(NULL);
    if (new_size < 0)
        throw MtrxNegativeSizeError("new_size < 0", __FILE__, __LINE__, ctime(&t_time));

    if (new_size == 0)
    {
        width = 0;
        height = 0;
        elems_num = 0;
        size = 0;
        alloc_data();
    }
    else
    {
        width = new_size;
        height = new_size;
        size = new_size;
        elems_num = width*height;
        alloc_data();

        for (auto &elem:*this)
            elem = Type();
    }
}

template<typename Type>
BaseMtrx<Type>::BaseMtrx(int new_width, int new_height)
{
    time_t t_time = time(NULL);
    if (new_width < 0)
        throw MtrxNegativeSizeError("new_width < 0", __FILE__, __LINE__, ctime(&t_time));
    else if (new_height < 0)
        throw MtrxNegativeSizeError("new_height < 0", __FILE__, __LINE__, ctime(&t_time));

    if (new_width == 0 || new_height == 0)
    {
        width = 0;
        height = 0;
        elems_num = 0;
        size = 0;
        alloc_data();
    }
    else
    {
        width = new_width;
        height = new_height;
        size = max(width, height);
        elems_num = width*height;
        alloc_data();

        reset();
    }
}

template<typename Type>
BaseMtrx<Type>::BaseMtrx(const BaseMtrx<Type> &mtrx)
{
    time_t t_time = time(NULL);
    if (mtrx.elems_num < 0)
        throw MtrxNegativeSizeError("mtrx elems_num < 0", __FILE__, __LINE__, ctime(&t_time));
    this->elems_num = mtrx.elemsNum();
    this->size = mtrx.size;
    this->width = mtrx.width;
    this->height = mtrx.height;

    alloc_data();

    for (int i = 0; i < this->elems_num; i++)
        this->data_ptr[i] = mtrx[i];
    //cout << "HERE copy constructor1" << endl;
}

template<typename Type>
BaseMtrx<Type> &BaseMtrx<Type>::operator =(const BaseMtrx<Type> &mtrx)
{
    time_t t_time = time(NULL);
    if (mtrx.elems_num < 0)
        throw MtrxNegativeSizeError("mtrx elems_num < 0", __FILE__, __LINE__, ctime(&t_time));
    this->elems_num = mtrx.elemsNum();
    this->size = mtrx.size;
    this->width = mtrx.width;
    this->height = mtrx.height;

    alloc_data();

    for (int i = 0; i < this->elems_num; i++)
        data_ptr[i] = mtrx[i];
    //cout << "HERE copy constructor2" << endl;
    return *this;
}

/*template<typename Type>
bool BaseMtrx<Type>::isEmpty() const noexcept
{
    return !elems_num;
}

template<typename Type>
int BaseMtrx<Type>::getSize() const noexcept
{
    return size;
}

template<typename Type>
int BaseMtrx<Type>::elemsNum() const noexcept
{
    return elems_num;
}*/

template<typename Type>
void BaseMtrx<Type>::reset() noexcept
{
    for (auto &elem:*this)
        elem = Type();
}

template<typename Type>
Iterator<Type> BaseMtrx<Type>::begin() noexcept
{
    return Iterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
Iterator<Type> BaseMtrx<Type>::end() noexcept
{
    return Iterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
ConstIterator<Type> BaseMtrx<Type>::cbegin() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
ConstIterator<Type> BaseMtrx<Type>::cend() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
ConstIterator<Type> BaseMtrx<Type>::begin() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
ConstIterator<Type> BaseMtrx<Type>::end() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
Type &BaseMtrx<Type>::getElem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw MtrxIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

template<typename Type>
const Type &BaseMtrx<Type>::getElem(int id) const
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw MtrxIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

template<typename Type>
Type &BaseMtrx<Type>::operator [](int id)
{
    return getElem(id);
}

template<typename Type>
const Type &BaseMtrx<Type>::operator [](int id) const
{
    return getElem(id);
}

template<typename Type>
Type &BaseMtrx<Type>::getElem(int i, int j)
{
    time_t t_time = time(NULL);
    if (i < 0 || i >= height)
        throw MtrxIndexError("i", __FILE__, __LINE__, ctime(&t_time));
    if (j < 0 || j >= width)
        throw MtrxIndexError("j", __FILE__, __LINE__, ctime(&t_time));
    return getElem(i*width+j);
}

template<typename Type>
const Type &BaseMtrx<Type>::getElem(int i, int j) const
{
    time_t t_time = time(NULL);
    if (i < 0 || i >= height)
        throw MtrxIndexError("i", __FILE__, __LINE__, ctime(&t_time));
    if (j < 0 || j >= width)
        throw MtrxIndexError("j", __FILE__, __LINE__, ctime(&t_time));
    return getElem(i*width+j);
}

template<typename Type>
Type &BaseMtrx<Type>::operator()(int i, int j)
{
    return getElem(i, j);
}

template<typename Type>
const Type &BaseMtrx<Type>::operator()(const int &i, const int &j) const
{
    return getElem(i, j);
}

template<typename Type>
void BaseMtrx<Type>::alloc_data()
{
    this->data_ptr.reset();
    if (elems_num != 0)
    {
        shared_ptr<Type[]> new_ptr(new Type[elems_num]);

        time_t t_time = time(NULL);
        if (!new_ptr)
            throw MtrxAllocError("Allocationg data_ptr error", __FILE__, __LINE__, ctime(&t_time));

        this->data_ptr = new_ptr;
    }
}

//CANT SPECIALIZE THIS OPERATOR WITH DOUBLE TYPE FOR SOME REASON!!!!!!!!!!!!!!
/*template<>
bool BaseMtrx<double>::operator ==(const BaseMtrx<double> &an_mtrx)
{
    if (this->elems_num != an_mtrx.elems_num &&
            this->width != an_mtrx.width &&
            this->height != an_mtrx.height)
        return false;

    bool res = true;
    for (int i = 0; i < elems_num; i++)
    {
        if (abs((*this)[i] - an_mtrx[i]) > EPS)
        {
            cout << (*this)[i] << "!=" << an_mtrx[i] << endl;
            res = false;
            break;
        }
    }

    //cout << "BaseMtrx<double> compare" << endl;
    return res;
}*/

template<typename Type>
bool BaseMtrx<Type>::operator ==(const BaseMtrx<Type> &an_mtrx) const
{
    if (this->elems_num != an_mtrx.elems_num ||
            this->width != an_mtrx.width ||
            this->height != an_mtrx.height)
        return false;

    bool res = true;
    for (int i = 0; i < elems_num; i++)
    {
        //if (this[i] != an_mtrx[i])
        if (this->getElem(i) != an_mtrx.getElem(i))
        {
            res = false;
            break;
        }
    }

    return res;
}

template<typename Type>
bool BaseMtrx<Type>::operator !=(const BaseMtrx<Type>& an_mtrx) const
{
    return !(*this == an_mtrx);
}

#endif // BASEMTRX_HPP
