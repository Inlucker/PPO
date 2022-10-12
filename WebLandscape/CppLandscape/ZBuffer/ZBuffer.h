#ifndef ZBUFFER_H
#define ZBUFFER_H

#include "../Matrix/BaseMtrx.hpp"

class ZBuffer : public BaseMtrx<double>
{
public:
    using BaseType = BaseMtrx<double>;  //alias, will be useful someday
    ZBuffer();
    ZBuffer(int new_width, int new_height);

    virtual void reset() noexcept;
};

ostream& operator <<(ostream& os, const ZBuffer& buf);

#endif // ZBUFFER_H
