#pragma once

class MyColor
{
public:
  MyColor() = default;
  MyColor(int r, int g, int b);

  bool operator ==(const MyColor& an_c) const;
  bool operator !=(const MyColor& an_c) const;

  void getRgb(int* r, int* g, int* b) const;

private:
  int red;
  int green;
  int blue;
};
