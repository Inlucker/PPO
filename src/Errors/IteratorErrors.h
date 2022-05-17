#ifndef ITERATORERRORS_H
#define ITERATORERRORS_H

#include "BaseError.h"

//ITERATOR
class IteratorWeakPtrError : public BaseError
{
public:
    IteratorWeakPtrError(string info, string filename, int line, const char *time, string error = "Iterator weak_ptr error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class IteratorIdError : public BaseError
{
public:
    IteratorIdError(string info, string filename, int line, const char *time, string error = "Iterator id out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

#endif // ITERATORERRORS_H
