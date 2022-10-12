#ifndef HEIGHTSMAPPOINTSERRORS_H
#define HEIGHTSMAPPOINTSERRORS_H

#include "BaseError.h"
//HeightsMapPoints
/*class HeightsMapPointsAllocError : public BaseError
{
public:
    HeightsMapPointsAllocError(string info, string filename, int line, const char *time, string error = "HeightsMapPoints alloc error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class HeightsMapPointsNegativeSizeError : public BaseError
{
public:
    HeightsMapPointsNegativeSizeError(string info, string filename, int line, const char *time, string error = "Trying to create HeightsMapPoints with negative size")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class HeightsMapPointsIndexError : public BaseError
{
public:
    HeightsMapPointsIndexError(string info, string filename, int line, const char *time, string error = "HeightsMapPoints index out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};*/

#endif // HEIGHTSMAPPOINTSERRORS_H
