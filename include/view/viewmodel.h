#ifndef VIEWMODEL_H_
#define VIEWMODEL_H_

#include <vector>

#include "model/world.h"


class ViewModel
{
private:
public:
    virtual void draw() = 0;
};

class CircleShape : public ViewModel
{
private:
    const float x;
    const float y;
    const float z;
    const float r;
public:
    CircleShape(float, float, float, float);
};

class BoxShape : public ViewModel
{
private:
    const float x;
    const float y;
    const float z;
    const float a;
    const float b;
    const float c;
public:
    BoxShape(float, float, float, float, float, float);
};


#endif /* VIEWMODEL_H_ */
