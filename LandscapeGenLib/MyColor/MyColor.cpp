#include "MyColor.h"

MyColor::MyColor(int r, int g, int b) : red(r), green(g), blue(b) {}

void MyColor::getRgb(int* r, int* g, int* b) const
{
  *r = red;
  *g = green;
  *b = blue;
}
