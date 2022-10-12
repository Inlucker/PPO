#ifndef HEIGHTSMAPERRORS_H
#define HEIGHTSMAPERRORS_H

#include "BaseError.h"

//HeightsMap
/*class HeightsMapAllocError : public BaseError
{
public:
    HeightsMapAllocError(string info, string filename, int line, const char *time, string error = "HeightsMap alloc error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class HeightsMapNegativeSizeError : public BaseError
{
public:
    HeightsMapNegativeSizeError(string info, string filename, int line, const char *time, string error = "Trying to create HeightsMap with negative size")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class HeightsMapIndexError : public BaseError
{
public:
    HeightsMapIndexError(string info, string filename, int line, const char *time, string error = "HeightsMap index out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};*/

#endif // HEIGHTSMAPERRORS_H
