#ifndef MTRXERRORS_H
#define MTRXERRORS_H

#include "BaseError.h"

//Mtrx
class MtrxAllocError : public BaseError
{
public:
    MtrxAllocError(string info, string filename, int line, const char *time, string error = "Mtrx alloc error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class MtrxNegativeSizeError : public BaseError
{
public:
    MtrxNegativeSizeError(string info, string filename, int line, const char *time, string error = "Trying to create Mtrx with negative size")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class MtrxIndexError : public BaseError
{
public:
    MtrxIndexError(string info, string filename, int line, const char *time, string error = "Mtrx index out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

#endif // MTRXERRORS_H
