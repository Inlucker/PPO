#ifndef BASEERRORS_H
#define BASEERRORS_H

#include <exception>
#include <string>

using namespace std;

class BaseError : public exception
{
public:
    BaseError(string info, string filename, int line, const char *time, string error = "Error")
    {
        err_info = "\nError: " + error;
        err_info = err_info + "\nTime: " + time;
        err_info += "File name: " + filename +"\nLine#: " + to_string(line);
        err_info += "\nWhat caused error: " + info;
    }
    virtual const char* what() const noexcept override
    {
        return err_info.c_str();
    }
protected:
    string err_info;
};

#endif // BASEERRORS_H
