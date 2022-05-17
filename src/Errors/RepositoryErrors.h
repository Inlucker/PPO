#ifndef REPOSITORYERRORS_H
#define REPOSITORYERRORS_H

#include "BaseError.h"

class ConnectionError : public BaseError
{
public:
    ConnectionError(string info, string filename, int line, const char *time, string error = "Connection error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class GetCanvasError : public BaseError
{
public:
    GetCanvasError(string info, string filename, int line, const char *time, string error = "Get canvas error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class InsertCanvasError : public BaseError
{
public:
    InsertCanvasError(string info, string filename, int line, const char *time, string error = "Insert canvas error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class DeleteCanvasError : public BaseError
{
public:
    DeleteCanvasError(string info, string filename, int line, const char *time, string error = "Delete canvas error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class UpdateCanvasError : public BaseError
{
public:
    UpdateCanvasError(string info, string filename, int line, const char *time, string error = "Update canvas error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

#endif // REPOSITORYERRORS_H
