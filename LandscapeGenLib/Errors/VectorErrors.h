#ifndef VECTORERRORS_H
#define VECTORERRORS_H

#include "BaseError.h"

//VECTOR
class VectorEmptyError : public BaseError
{
public:
    VectorEmptyError(string info, string filename, int line, const char *time, string error = "Trying to use empty vector")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class VectorNegativeSizeError : public BaseError
{
public:
    VectorNegativeSizeError(string info, string filename, int line, const char *time, string error = "Trying to create vector with negative size")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class VectorMemoryError : public BaseError
{
public:
    VectorMemoryError(string info, string filename, int line, const char *time, string error = "Memory error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class VectorIndexError : public BaseError
{
public:
    VectorIndexError(string info, string filename, int line, const char *time, string error = "Index out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class VectorDifSizeError : public BaseError
{
public:
    VectorDifSizeError(string info, string filename, int line, const char *time, string error = "Opearation with different sized vectors")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class VectorZeroDivError : public BaseError
{
public:
    VectorZeroDivError(string info, string filename, int line, const char *time, string error = "Division on zero")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class VectorSizeError : public BaseError
{
public:
    VectorSizeError(string info, string filename, int line, const char *time, string error = "Wrong size for vector multiplicationg")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

#endif // VECTORERRORS_H
