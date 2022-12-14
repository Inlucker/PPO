#ifndef CANVASMOTHER_H
#define CANVASMOTHER_H

#include "Essensities/CanvasBL.h"

class CanvasMother
{
public:
    CanvasMother() = delete;

    static shared_ptr<CanvasBL> withSize(int size);
};

#endif // CANVASMOTHER_H
