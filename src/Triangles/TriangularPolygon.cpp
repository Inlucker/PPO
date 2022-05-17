#include "TriangularPolygon.h"

// Add Errors?

TriangularPolygon::TriangularPolygon() : TriangularPolygon(make_shared<Point>(), make_shared<Point>(), make_shared<Point>())
{

}

TriangularPolygon::TriangularPolygon(shared_ptr<Point> new_p1, shared_ptr<Point> new_p2, shared_ptr<Point> new_p3) : p1(new_p1), p2(new_p2), p3(new_p3)
{
    calcRect();
    calcNormals();
    calcSurface();
    calcIntensity();
    //calcColor();
    //color = Qt::gray;
    //color = QColor(rand()%128+64, rand()%128+64, rand()%128+64);
}

/*TriangularPolygon::TriangularPolygon::TriangularPolygon(shared_ptr<Point> new_p1, shared_ptr<Point> new_p2, shared_ptr<Point> new_p3, color_t c) : p1(new_p1), p2(new_p2), p3(new_p3), color(c)
{
    calcRect();
    calcNormals();
    calcSurface();
}*/

double TriangularPolygon::getZ(double x, double y) const
{
    //Ax+By+Cz+D=0 => Cz = -Ax-By-D => z = (-Ax-By-D)/C
    if (C != 0)
        return (-A*x-B*y-D)/C;
    else
    {
        return INT_MIN;//ToDo?
    }
}

double TriangularPolygon::getIntensity() const
{
    return intensity;
}

/*void TriangularPolygon::swap(Point &p1, Point &p2)
{
    Point tmp = p1;
    p1 = p2;
    p2 = tmp;
}*/

bool TriangularPolygon::isInRect(double x, double y) const
{
    return (x >= min_x && x <= max_x && y >= min_y && y <= max_y);
}

bool TriangularPolygon::isInTriangle(double x, double y) const
{
    //x1*x2+y1*y2
    if ((x - p1->getX())*norm_vec1[0] + (y - p1->getY())*norm_vec1[1] < 0 ||
        (x - p2->getX())*norm_vec2[0] + (y - p2->getY())*norm_vec2[1] < 0 ||
        (x - p3->getX())*norm_vec3[0] + (y - p3->getY())*norm_vec3[1] < 0)
        return false;
    else
        return true;
}

const Point& TriangularPolygon::getP1() const
{
    return *p1;
}

const Point& TriangularPolygon::getP2() const
{
    return *p2;
}

const Point& TriangularPolygon::getP3() const
{
    return *p3;
}

Point& TriangularPolygon::getP1()
{
    return *p1;
}

Point& TriangularPolygon::getP2()
{
    return *p2;
}

Point& TriangularPolygon::getP3()
{
    return *p3;
}

void TriangularPolygon::update()
{
    calcRect();
    calcNormals();
    calcSurface();
    //calcIntensity();
}

/*int TriangularPolygon::getP1() const
{
    return p1;
}

int TriangularPolygon::getP2() const
{
    return p2;
}

int TriangularPolygon::getP3() const
{
    return p3;
}*/

/*void TriangularPolygon::setPoints(const Point& new_p1, const Point& new_p2, const Point& new_p3)
{
    p1 = new_p1;
    p2 = new_p2;
    p3 = new_p3;

    calcRect();
    calcNormals();
    calcSurface();
}*/

void TriangularPolygon::calcRect()
{
    min_x = p1->getX();
    max_x = p1->getX();
    min_y = p1->getY();
    max_y = p1->getY();

    if (p2->getX() < min_x)
        min_x = p2->getX();
    if (p2->getX() > max_x)
        max_x = p2->getX();
    if (p2->getY() < min_y)
        min_y = p2->getY();
    if (p2->getY() > max_y)
        max_y = p2->getY();

    if (p3->getX() < min_x)
        min_x = p3->getX();
    if (p3->getX() > max_x)
        max_x = p3->getX();
    if (p3->getY() < min_y)
        min_y = p3->getY();
    if (p3->getY() > max_y)
        max_y = p3->getY();
}

void TriangularPolygon::calcNormals()
    {
    // Обязательно? по часовой, чтобы получить внутренние нормали
    /*Vector vec1 = {p2->getX() - p1->getX(), p2->getY() - p1->getY()};
    Vector vec2 = {p3->getX() - p2->getX(), p3->getY() - p2->getY()};
    Vector vec3 = {p1->getX() - p3->getX(), p1->getY() - p3->getY()};*/
    double vec1_x = p2->getX() - p1->getX(), vec1_y = p2->getY() - p1->getY();
    double vec2_x = p3->getX() - p2->getX(), vec2_y = p3->getY() - p2->getY();
    double vec3_x = p1->getX() - p3->getX(), vec3_y = p1->getY() - p3->getY();

    //cout << vec1 << vec2 << vec3 << endl;

    /*if (vec1[1] != 0)
        norm_vec1 = {1, -vec1[0]/vec1[1]};*/
    if (vec1_y != 0)
        norm_vec1 = {1, -vec1_x/vec1_y};
    else
        norm_vec1 = {0, 1};
    //Зависит от того, идут ли точки по часовой, или против.
    //if (norm_vec1 * vec2 < 0)
    if (norm_vec1[0]*vec2_x + norm_vec1[1]*vec2_y < 0)
        norm_vec1 = norm_vec1*(-1.);

    /*if (vec2[1] != 0)
        norm_vec2 = {1, -vec2[0]/vec2[1]};*/
    if (vec2_y != 0)
        norm_vec2 = {1, -vec2_x/vec2_y};
    else
        norm_vec2 = {0, 1};
    //Зависит от того, идут ли точки по часовой, или против.
    //if (norm_vec2 * vec3 < 0)
    if (norm_vec2[0]*vec3_x + norm_vec2[1]*vec3_y < 0)
        norm_vec2 = norm_vec2*(-1.);

    /*if (vec3[1] != 0)
        norm_vec3 = {1, -vec3[0]/vec3[1]};*/
    if (vec3_y != 0)
        norm_vec3 = {1, -vec3_x/vec3_y};
    else
        norm_vec3 = {0, 1};
    //Зависит от того, идут ли точки по часовой, или против.
    //if (norm_vec3 * vec1 < 0)
    if (norm_vec3[0]*vec1_x + norm_vec3[1]*vec1_y < 0)
        norm_vec3 = norm_vec3*(-1.);

    //cout << norm_vec1 << norm_vec2 << norm_vec3 << endl;
}

void TriangularPolygon::calcSurface()
{
    double x1 = p1->getX(), y1 = p1->getY(), z1 = p1->getZ();
    double x2 = p2->getX(), y2 = p2->getY(), z2 = p2->getZ();
    double x3 = p3->getX(), y3 = p3->getY(), z3 = p3->getZ();
    A = y1 *(z2 - z3) + y2 *(z3 - z1) + y3 *(z1 - z2);
    B = z1 *(x2 - x3) + z2 *(x3 - x1) + z3 *(x1 - x2);
    C = x1 *(y2 - y3) + x2 *(y3 - y1) + x3 *(y1 - y2);
    D = -(x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) + x3 * (y1 * z2 - y2 * z1));
}

/*void TriangularPolygon::calcColor()
{
    color = QColor(20, 150, 20);//Qt::darkGreen;//Qt::green;//QColor(200, 200, 200);
    if (A != 0 || B != 0 || C != 0)
    {
        double cosinus = fabs(B/sqrt(A*A+B*B+C*C)); //Right?

        //color.setHsvF(color.hsvHueF(), color.hsvSaturationF(), 0.15+float(cosinus*0.75));
        color = QColor(color.red()*cosinus, color.green()*cosinus, color.blue()*cosinus);
    }
}*/

void TriangularPolygon::calcIntensity()
{
    if (A != 0 || B != 0 || C != 0)
    {
        intensity = fabs(B/sqrt(A*A+B*B+C*C));
    }
    else
    {
        intensity = 1;
    }
}

ostream& operator <<(ostream& os, const TriangularPolygon& pol)
{
    os << pol.p1 << pol.p2 << pol.p3 << endl;
    os << "A  = " << pol.A << "; B = " << pol.B << "; C = " << pol.C << "; D = " << pol.D << endl;
    //cout << norm_vec1 << norm_vec2 << norm_vec3 << endl;
    //cout << "min_x = " << min_x << "; max_x = " << max_x << "; min_y = " << min_y << "; max_y = " << max_y << endl;
    return os;
}
