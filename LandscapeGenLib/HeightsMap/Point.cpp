#include "Point.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include <cmath>

Point::Point()
{
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(const double new_x, const double new_y, const double new_z)
{
    x = new_x;
    y = new_y;
    z = new_z;
}

void Point::transform(const Point moveK, const Point scaleK, const Point rotateK, const Point center)
{
    move(moveK);
    scale(scaleK, center);
    rotate(rotateK, center);
}

void Point::transform(const Point moveK, const Point scaleK, const Point rotateK)
{
    move(moveK);
    scale(scaleK, *this);
    rotate(rotateK);
    //rotate(rotateK);
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

double Point::getZ() const
{
    return z;
}

void Point::setX(double new_x)
{
    x = new_x;
}

void Point::setY(double new_y)
{
    y = new_y;
}

void Point::setZ(double new_z)
{
    z = new_z;
}

bool Point::operator ==(Point &an_p) const
{
    bool res = true;
    if (abs(this->x - an_p.x) > EPS ||
            abs(this->y - an_p.y) > EPS ||
            abs(this->z - an_p.z) > EPS)
        res = false;
    return res;
}

bool Point::operator !=(Point &an_p) const
{
    return !(*this == an_p);
}

void Point::move(const Point move)
{
    x += move.getX();
    y += move.getY();
    z += move.getZ();
}

void Point::scale(const Point scale, const Point center)
{
    double kx = scale.getX();
    double ky = scale.getY();
    double kz = scale.getZ();
    double xc = center.getX();
    double yc = center.getY();
    double zc = center.getZ();
    x = kx * x + xc * (1 - kx);
    y = ky * y + yc * (1 - ky);
    z = kz * z + zc * (1 - kz);
}


void Point::rotateX(const double angle, const Point center)
{
    //double xc = center.getX();
    double yc = center.getY();
    double zc = center.getZ();
    double radians = angle * M_PI / 180;
    double tmp_y = y;
    double tmp_z = z;
    y = yc + (tmp_y - yc) * cos(radians) + (tmp_z - zc) * sin(radians);
    z = zc - (tmp_y - yc) * sin(radians) + (tmp_z - zc) * cos(radians);
}

void Point::rotateY(const double angle, const Point center)
{
    double xc = center.getX();
    //double yc = center.getY();
    double zc = center.getZ();
    double radians = angle * M_PI / 180;
    double tmp_x = x;
    double tmp_z = z;
    x = xc + (tmp_x - xc) * cos(radians) + (tmp_z - zc) * sin(radians);
    z = zc - (tmp_x - xc) * sin(radians) + (tmp_z - zc) * cos(radians);
}

void Point::rotateZ(const double angle, const Point center)
{
    double xc = center.getX();
    double yc = center.getY();
    //double zc = center.getZ();
    double radians = angle * M_PI / 180;
    double tmp_x = x;
    double tmp_y = y;
    x = xc + (tmp_x - xc) * cos(radians) - (tmp_y - yc) * sin(radians);
    y = yc + (tmp_x - xc) * sin(radians) + (tmp_y - yc) * cos(radians);
}

void Point::rotateX(const double angle)
{
    double radians = angle * M_PI / 180;
    double tmp_y = y;
    double tmp_z = z;
    y = tmp_y * cos(radians) + tmp_z * sin(radians);
    z  = -tmp_y * sin(radians) + tmp_z * cos(radians);
}

void Point::rotateY(const double angle)
{
    double radians = angle * M_PI / 180;
    double tmp_x = x;
    double tmp_z = z;
    x = tmp_x * cos(radians) + tmp_z * sin(radians);
    z = -tmp_x * sin(radians) + tmp_z * cos(radians);
}

void Point::rotateZ(const double angle)
{
    double radians = angle * M_PI / 180;
    double tmp_x = x;
    double tmp_y = y;
    x = tmp_x * cos(radians) - tmp_y * sin(radians);
    y = tmp_x * sin(radians) + tmp_y * cos(radians);
}

void Point::rotate(const Point rotate, const Point center)
{
    rotateX(rotate.getX(), center);
    rotateY(rotate.getY(), center);
    rotateZ(rotate.getZ(), center);
}

void Point::rotate(const Point rotate)
{
    rotateX(rotate.getX());
    rotateY(rotate.getY());
    rotateZ(rotate.getZ());
}

ostream& operator <<(ostream& os, const Point& point)
{
    os << "(" << point.getX() << ", " << point.getY() << ", " << point.getZ() << ")";
    //os << point.getX() << " " << point.getY() << " " << point.getZ() << " ";

    return os;
}
