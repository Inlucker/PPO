#ifndef HEIGHTSMAPBUILDER_H
#define HEIGHTSMAPBUILDER_H

#include "HeightsMap/HeightsMap.h"

class HeightsMapBuilder
{
public:
    HeightsMapBuilder() = default;

    shared_ptr<HeightsMap> build();
    HeightsMapBuilder* withSize(int size);
    HeightsMapBuilder* withGen(bool gen);

private:
    int m_size = 0;
    bool gen_flag = true;
};

#endif // HEIGHTSMAPBUILDER_H
