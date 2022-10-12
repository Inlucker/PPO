#pragma once

class MyColor
{
public:
  MyColor() = default;
  MyColor(int r, int g, int b);

  void getRgb(int* r, int* g, int* b) const;

private:
  int red;
  int green;
  int blue;

};