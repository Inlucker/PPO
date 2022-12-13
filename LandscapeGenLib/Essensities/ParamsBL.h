#ifndef PARAMSBL_H
#define PARAMSBL_H


class ParamsBL
{
public:
    ParamsBL() = delete;
    ParamsBL(int c_id, int w, int h, double ran, bool s, int m, int r, int g, int b, int siz);

    bool operator ==(ParamsBL& an_p) const;
    bool operator !=(ParamsBL& an_p) const;

    int getCanvasID() noexcept;
    int getWidth() noexcept;
    int getHeight() noexcept;
    double getRange() noexcept;
    bool getSmooth() noexcept;
    int getMult() noexcept;
    int getRed() noexcept;
    int getGreen() noexcept;
    int getBlue() noexcept;
    int getSize() noexcept;

private:
    int canvas_id, width, height;
    double range;
    int mult, red, green, blue, size;
    bool smooth;
};

#endif // PARAMSBL_H
