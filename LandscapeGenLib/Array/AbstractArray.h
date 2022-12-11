#ifndef ABSTRACTARRAY_H
#define ABSTRACTARRAY_H

class AbstractArray
{
public:
    AbstractArray();
    virtual ~AbstractArray() = 0;

    virtual bool isEmpty() const noexcept = 0;
    virtual int size() const noexcept = 0;
    virtual int elemsNum() const noexcept = 0;

protected:
    virtual void alloc_data() = 0;

protected:
    int elems_num = -1;
};

#endif // ABSTRACTARRAY_H
