#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "../Matrix/BaseMtrx.hpp"

#include <QColor>
#include "../MyColor/MyColor.h"

typedef MyColor color_t;

class FrameBuffer : public BaseMtrx<color_t>
{
public:
    using BaseType = BaseMtrx<color_t>;  //alias, will be useful someday
    FrameBuffer();
    FrameBuffer(int new_width, int new_height);

    virtual void reset() noexcept;
};

ostream& operator <<(ostream& os, const FrameBuffer& map);

#endif // FRAMEBUFFER_H
