#ifndef ABSTRACTVECTOR_H
#define ABSTRACTVECTOR_H

class AbstractVector
{
public:
    AbstractVector();
    virtual ~AbstractVector() = 0;

    virtual bool isEmpty() const = 0;
    virtual int size() const = 0;
protected:
    int elems_num;
};

#endif // ABSTRACTVECTOR_H
