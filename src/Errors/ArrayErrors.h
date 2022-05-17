#ifndef ARRAYERRORS_H
#define ARRAYERRORS_H

#include "BaseError.h"

//Array
class ArrayAllocError : public BaseError
{
public:
    ArrayAllocError(string info, string filename, int line, const char *time, string error = "Array alloc error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class ArrayNegativeSizeError : public BaseError
{
public:
    ArrayNegativeSizeError(string info, string filename, int line, const char *time, string error = "Trying to create Array with negative size")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class ArrayIndexError : public BaseError
{
public:
    ArrayIndexError(string info, string filename, int line, const char *time, string error = "Array index out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

#endif // ARRAYERRORS_H
