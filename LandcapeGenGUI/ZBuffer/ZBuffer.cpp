#include "ZBuffer.h"

#include "Matrix/BaseMtrx.hpp"

ZBuffer::ZBuffer()
{
    reset();
}

ZBuffer::ZBuffer(int new_width, int new_height) : BaseType(new_width, new_height)
{
    reset();
}

void ZBuffer::reset() noexcept
{
    for (auto &elem:*this)
        elem = INT_MIN;
}

ostream& operator <<(ostream& os, const ZBuffer& buf)
{
    if (buf.isEmpty())
    {
        os << "ZBuffer is empty.";
        return os;
    }

    ConstIterator<double> It = buf.cbegin();
    for (int i = 0; i < buf.getHeight() && It != buf.cend(); i++)
    {
        os << '\n' << '[' << *It++;
        for (int j = 1; j < buf.getWidth() && It != buf.cend(); It++, j++)
            os << "; " << *It ;
        os << ']';
    }
    os << endl;

    return os;
}
