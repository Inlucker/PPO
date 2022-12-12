#include "CanvasBL.h"

/*CanvasBL::CanvasBL(string fn1, string fn2, string fn3)
{
    string res = strFromFile(fn1);
    heights_map = HeightsMap(res);
    res = strFromFile(fn2);
    heights_map_points = HeightsMapPoints(res);

    ifstream file(fn3); //NEED TO ADD EXCEPTION, WHEN NO SUCH FILE
    file >> red >> green >> blue;
    file.close();
}*/


CanvasBL::CanvasBL(int _id, int u_id, string n, string &hm, string &tpa, string &c) : id(_id), user_id(u_id), name(n)
{
    heights_map = HeightsMap(hm);
    heights_map_points = HeightsMapPoints(tpa);

    int i = 0;
    string tmp = "";
    while (c[i] != ' ' && c[i] != '\n' && c[i] != '\0')
    {
        tmp += c[i++];
    }
    red = stoi(tmp);
    i++;
    tmp = "";

    while (c[i] != ' ' && c[i] != '\n' && c[i] != '\0')
    {
        tmp += c[i++];
    }
    green = stoi(tmp);
    i++;
    tmp = "";

    while (c[i] != ' ' && c[i] != '\n' && c[i] != '\0')
    {
        tmp += c[i++];
    }
    blue = stoi(tmp);
    i++;
    tmp = "";
}

CanvasBL::CanvasBL(int _id, int u_id, string n, HeightsMap &hm, HeightsMapPoints &hmp, int r, int g, int b) : id(_id), user_id(u_id), name(n)
{
    heights_map = hm;
    heights_map_points = hmp;
    red = r;
    green = g;
    blue = b;
}

bool CanvasBL::operator ==(CanvasBL &an_c)
{
    bool res = true;

    if (this->user_id != an_c.user_id ||
            this->name != an_c.name ||
            this->heights_map != an_c.heights_map ||
            this->heights_map_points != an_c.heights_map_points ||
            this->red != an_c.red ||
            this->green != an_c.green ||
            this->blue != an_c.blue)
        res = false;
    return res;
}

bool CanvasBL::operator !=(CanvasBL &an_c)
{
    return !(*this == an_c);
}

int CanvasBL::getId()
{
    return id;
}

int CanvasBL::getUserId()
{
    return user_id;
}

string CanvasBL::getName()
{
    return name;
}

HeightsMap &CanvasBL::getHeightsMap()
{
    return heights_map;
}

HeightsMapPoints &CanvasBL::getHeightsMapPoints()
{
    return heights_map_points;
}

void CanvasBL::getColor(int &r, int &g, int &b) noexcept
{
    r = red;
    g = green;
    b = blue;
}

void CanvasBL::getColor(string &c) noexcept
{
    c = to_string(red) + " " + to_string(green) + " " + to_string(blue);
}

string CanvasBL::strFromFile(string file_name)
{
    string res = "";
    ifstream file(file_name); //NEED TO ADD EXCEPTION, WHEN NO SUCH FILE

    string tmp = "";
    while (file >> tmp)
        res += tmp + " ";
    file.close();
    return res;
}
