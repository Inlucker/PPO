#ifndef PARAMSBL_H
#define PARAMSBL_H


class ParamsBL
{
public:
    ParamsBL() = delete;
    ParamsBL(int c_id, int w, int h, int ran, bool s, int m, int r, int g, int b, int siz);

    int getCanvasID() noexcept;
    int getWidth() noexcept;
    int getHeight() noexcept;
    int getRange() noexcept;
    bool getSmooth() noexcept;
    int getMult() noexcept;
    int getRed() noexcept;
    int getGreen() noexcept;
    int getBlue() noexcept;
    int getSize() noexcept;

private:
    int canvas_id, width, height, range, mult, red, green, blue, size;
    bool smooth;
};

#endif // PARAMSBL_H
