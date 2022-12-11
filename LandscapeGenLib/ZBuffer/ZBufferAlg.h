#ifndef ZBUFFERALG_H
#define ZBUFFERALG_H

#include <iostream>
#include <memory>

using namespace std;

#include "ZBuffer.h"
#include "FrameBuffer.h"
class TriPolArray;
class Point;

class ZBufferAlg
{
public:
    ZBufferAlg() = delete;
    ZBufferAlg(int new_width, int new_height);

    void execute(TriPolArray &mas);
    void executeFT(TriPolArray &mas, int first, int last, int red, int green, int blue);
    void execute2(TriPolArray &mas); //Boost and fix white lines

    shared_ptr<FrameBuffer> getFrameBuffer() const noexcept;
private:
    vector<double> interpolate(double i0, double d0, double i1, double d1) const;
    void addInterpolate(vector<double> &values, double i0, double d0, double i1, double d1) const;
    void swap(Point &p1, Point &p2);

private:
    shared_ptr<ZBuffer> zbuffer;
    shared_ptr<FrameBuffer> frame_buffer;
    int width;
    int height;
};

#endif // ZBUFFERALG_H
