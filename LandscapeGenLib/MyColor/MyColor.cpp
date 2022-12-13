#include "MyColor.h"

MyColor::MyColor(int r, int g, int b) : red(r), green(g), blue(b) {}

bool MyColor::operator ==(const MyColor &an_c) const
{
    return (this->red == an_c.red &&
            this->green == an_c.green &&
            this->blue == an_c.blue);
}

bool MyColor::operator !=(const MyColor &an_c) const
{
    return !(*this == an_c);
}

void MyColor::getRgb(int* r, int* g, int* b) const
{
  *r = red;
  *g = green;
  *b = blue;
}
