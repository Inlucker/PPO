#include "HeightsMap.h"

#include <time.h>
#include <random>
#include <fstream>

#include "Iterator/Iterator.hpp"
#include "Iterator/ConstIterator.hpp"
#include "Errors/HeightsMapErrors.h"
#include "HeightsMapPoints.h"

HeightsMap::HeightsMap()
{
    max_height = 0;
}

HeightsMap::HeightsMap(int new_size) : BaseType(new_size)
{
    max_height = 0;
}

HeightsMap::HeightsMap(string& hm)
{
    int i = 0;
    string tmp = "";
    while (hm[i] != ' ' && hm[i] != '\n' && hm[i] != '\0')
    {
        tmp += hm[i];
        i++;
    }
    width = stoi(tmp);
    i++;
    tmp = "";

    while (hm[i] != ' ' && hm[i] != '\n' && hm[i] != '\0')
    {
        tmp += hm[i];
        i++;
    }
    height = stoi(tmp);
    i++;
    tmp = "";

    changeSizes(width, height);

    for (auto& elem : *this)
    {
        while (hm[i] != ' ' && hm[i] != '\n' && hm[i] != '\0')
        {
            tmp += hm[i];
            i++;
        }
        elem = stod(tmp);
        i++;
        tmp = "";
    }

    calcMaxHeight();
}

double HeightsMap::getMaxHeight()
{
    return max_height;
}

double HeightsMap::getMinHeight()
{
    if (elems_num > 0)
    {
        double min_height = (*this)[0];
        for (auto& elem : *this)
            if (elem < min_height)
                min_height = elem;
        return min_height;
    }
    else
    {
        return 0;
    }
}

void HeightsMap::resetHeightsmap() noexcept
{
    for (auto &elem:*this)
        elem = 0;
    max_height = 0;
}

void HeightsMap::diamondSquare()
{
    diamondSquare(DS_RANGE);
}

/*void HeightsMap::diamondSquare(float r)
{
    resetHeightsmap();

    //(*this)(0, 0) = 0;
    //(*this)(0, size - 1) = 0;
    //(*this)(size - 1, 0) = 0;
    //(*this)(size - 1, size - 1) = 0;

    diamondSquare(0, 0, size-1, size-1, r, size-1); // size-1
}*/

void HeightsMap::diamondSquare(float r, bool smoothing)
{
    resetHeightsmap();

    diamondSquare(0, 0, size-1, size-1, r, size-1);
    if (smoothing)
        smoothHeightsMap(1, 1, height-1, width-1, 1);

    calcMaxHeight();
}

void HeightsMap::simpleGen(double r, int n)
{
    //cout << n << endl;
    randomizeHeightsMap(1, 1, height-2, width-2, r);
    smoothHeightsMap(1, 1, height-1, width-1, n);

    calcMaxHeight();
}

void HeightsMap::readFromFile(string file_name)
{
    ifstream file(file_name); //NEED TO ADD EXCEPTION, WHEN NO SUCH FILE
    //file.open(file_name);

    file >> width;
    file >> height;

    changeSizes(width, height);

    for (auto& elem : *this)
    {
        file >> elem;
    }
    file.close();

    calcMaxHeight();
}

void HeightsMap::writeToFile(string file_name)
{
    ofstream file(file_name);
    file << width << " ";
    file << height << " ";
    for (auto& elem : *this)
    {
        file << to_string(elem) << " ";
    }
    file.close();
}

void HeightsMap::toStr(string& res)
{
    res = "";
    res += to_string(width) + " ";
    res += to_string(height) + " ";
    for (auto& elem : *this)
    {
        res += to_string(elem) + " ";
    }
}

shared_ptr<HeightsMapPoints> HeightsMap::createPoints(double kx, double ky, double kz)
{
    //shared_ptr<HeightsMapPoints> new_points_map = make_shared<HeightsMapPoints>(size);
    shared_ptr<HeightsMapPoints> new_points_map = make_shared<HeightsMapPoints>(width, height);
    if (width > 0 && height > 0)
    {
        ConstIterator<height_t> map_it = this->cbegin();
        int i = 0;
        for (auto& points_it : *new_points_map)
        {
            points_it = make_shared<Point>(double(i/width) * kx, double(*map_it) * ky, double(i % width) * kz); //почему работает именно с width????
            map_it++;
            i++;
        }
        new_points_map->updateCenter();
    }
    return new_points_map;
}

shared_ptr<HeightsMapPoints> HeightsMap::createPoints()
{
    return createPoints(1, 1, 1);
}

bool HeightsMap::operator ==(HeightsMap &an_mtrx) const
{
    if (this->elems_num != an_mtrx.elems_num &&
            this->width != an_mtrx.width &&
            this->height != an_mtrx.height)
        return false;

    bool res = true;
    for (int i = 0; i < elems_num; i++)
    {
        /*double test1 = (*this)[i];
        double test2 = an_mtrx[i];
        double eps = EPS;*/
        if (fabs((*this)[i]-an_mtrx[i]) > EPS)
        {
            printf("%.7f != %.7f\n", (*this)[i], an_mtrx[i]);
            //cout << (*this)[i] << " != " << an_mtrx[i] << endl;
            res = false;
            break;
        }
    }

    //cout << "HeightsMap compared" << endl;
    return res;
}

bool HeightsMap::operator !=(HeightsMap &an_mtrx) const
{
    return !(*this == an_mtrx);
}

void HeightsMap::changeSizes(int new_width, int new_height)
{
    time_t t_time = time(NULL);
    if (new_width < 0)
        throw MtrxNegativeSizeError("new_width < 0", __FILE__, __LINE__, ctime(&t_time));
    else if (new_height < 0)
        throw MtrxNegativeSizeError("new_height < 0", __FILE__, __LINE__, ctime(&t_time));

    if (new_width == 0 || new_height == 0)
    {
        width = 0;
        height = 0;
        elems_num = 0;
        size = 0;
        alloc_data();
    }
    else
    {
        width = new_width;
        height = new_height;
        size = min(width, height);
        elems_num = width*height;
        alloc_data();

        reset();
    }
}

void HeightsMap::diamondSquare(unsigned x1, unsigned y1, unsigned x2, unsigned y2, float range, unsigned level)
{
    if (level < 1)
    {
        //cout << *this << endl;
        return;
    }

    //cout << "Range = " << range << endl;
    //cout << "Level = " << level << endl;

    // diamonds
    for (unsigned i = x1 + level; i < x2; i += level)
        for (unsigned j = y1 + level; j < y2; j += level)
        {
            float a = (*this)(i - level, j - level);
            //cout << "a = (" << i - level << ", " << j - level << ") = " << a << endl;
            float b = (*this)(i, j - level);
            //cout << "b = (" << i << ", " << j - level << ") = " << b << endl;
            float c = (*this)(i - level, j);
            //cout << "c = (" << i - level << ", " << j << ") = " << c << endl;
            float d = (*this)(i, j);
            //cout << "d = (" << i << ", " << j << ") = " << d << endl;
            float e = (*this)(i - level / 2, j - level / 2) = (a + b + c + d) / 4 + (getRnd() * range);
            //cout << "e = (" << i - level/2 << ", " << j - level/2 << ") = " << e << endl;
            //cout << *this << endl;
        }

    //cout << *this << endl;

    // squares
    for (unsigned i = x1 + 2 * level; i < x2; i += level)
        for (unsigned j = y1 + 2 * level; j < y2; j += level)
        {
            float a = (*this)(i - level, j - level);
            //cout << "a = (" << i - level << ", " << j - level << ") = " << a << endl;
            float b = (*this)(i, j - level);
            //cout << "b = (" << i << ", " << j - level << ") = " << b << endl;
            float c = (*this)(i - level, j);
            //cout << "c = (" << i - level << ", " << j << ") = " << c << endl;
            //float d = (*this)(i, j);
            float e = (*this)(i - level / 2, j - level / 2);
            //cout << "e = (" << i - level/2 << ", " << j - level/2 << ") = " << e << endl;


            //cout << "?1 = (" << i - 3 * level / 2 << ", " << j - level / 2 << ") = " << (*this)(i - 3 * level / 2, j - level / 2) << endl;
            float f = (*this)(i - level, j - level / 2) = (a + c + e + (*this)(i - 3 * level / 2, j - level / 2)) / 4 + (getRnd() * range);
            //cout << "f = (" << i - level << ", " << j - level/2 << ") = " << f << endl;
            //cout << *this << endl;
            //cout << "?2 = (" << i - 3 * level / 2 << ", " << j - level / 2 << ") = " << (*this)(i - 3 * level / 2, j - level / 2) << endl;
            float g = (*this)(i - level / 2, j - level) = (a + b + e + (*this)(i - level / 2, j - 3 * level / 2)) / 4 + (getRnd() * range);
            //cout << "g = (" << i - level/2 << ", " << j - level << ") = " << g << endl;
            //cout << *this << endl;
        }

    //cout << *this << endl;

    diamondSquare(x1, y1, x2, y2, range / 2, level / 2);
}

void HeightsMap::diamondSquare2(int x1, int y1, int x2, int y2, float range, unsigned level)
{
    if (level < 1)
    {
        //cout << *this << endl;
        return;
    }

    int half_level = level/2;

    // diamonds
    for (int x = x1; x < x2; x += level)
        for (int y = y1; y < y2; y += level)
        {
            float a = (*this)(x, y);
            float b = (*this)(x + level, y);
            float c = (*this)(x, y + level);
            float d = (*this)(x + level, y + level);


            if (x + half_level == x1 || x + half_level == x2|| y + half_level == y1 || y + half_level == y2)
                float e = (*this)(x + half_level, y + half_level) = 0;
            else
                float e = (*this)(x + half_level, y + half_level) = (a + b + c + d) / 4 + (getRnd() * range);

            //cout << *this << endl;
        }

    // squares
    bool flag = false;
    for (int x = 0; x <= x2-x1; x += max(half_level, 1))
    {
        flag = !flag;
        for (int y = y1; y <= y2; y += level)
        {
            if (flag && y == y1)
                y += half_level;

            float f = 0;
            float g = 0;
            float h = 0;
            float i = 0;

            if (x - half_level >= x1 && y - half_level >= y1 && x + half_level <= x2 && y + half_level <= y2)
            {
                f = (*this)(x - half_level, y);
                g = (*this)(x, y - half_level);
                h = (*this)(x + half_level, y);
                i = (*this)(x, y + half_level);
            }

            if (x == x1 || x == x2|| y == y1 || y == y2)
                float e = (*this)(x, y) = 0;
            else
                float e = (*this)(x, y) = (f + g + h + i) / 4 + (getRnd() * range);

            //cout << *this << endl;
        }
    }

    diamondSquare2(x1, y1, x2, y2, range / 2, level / 2);
}

double HeightsMap::getRnd() const noexcept
{
    return (double)rand() / RAND_MAX;
}

void HeightsMap::randomizeHeightsMap(int x1, int y1, int x2, int y2, double n) noexcept
{
    srand(time(0));
    for (int i = y1; i <= y2; i++)
        for (int j = x1; j <= x2; j++)
            (*this)(i, j) = (getRnd() * n);
}

void HeightsMap::smoothHeightsMap(int x1, int y1, int x2, int y2, int n) noexcept
{
    for (int k = 0; k < n; k++)
        for (int i = y1; i < y2; i++)
            for (int j = x1; j < x2; j++)
            {
                double tmp_sum = 0;
                int tmp_n = 0;

                //cout << "(";
                double tmp = getValue(i-1, j-1);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i-1, j);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i-1, j+1);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i, j-1);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i, j);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i, j+1);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i+1, j-1);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i+1, j);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i+1, j+1);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                data_ptr[i*size+j] = tmp_sum / tmp_n;
                //cout  << ")/" << tmp_n << " = "<< tmp_sum << "/" << tmp_n << " = " << heights_map[i][j] << endl;
            }
}

double HeightsMap::getValue(int i, int j)
{
    if (i >= 0 && i <= size && j >= 0 && j <= size)
    {
        return data_ptr[i*size+j];
    }
    else
        return -1;
}

void HeightsMap::calcMaxHeight()
{
    if (elems_num > 0)
    {
        max_height = (*this)[0];
        for (auto& elem : *this)
            if (elem > max_height)
                max_height = elem;
    }
    else
    {
        max_height = 0;
    }
}

string HeightsMap::strFromFile(string file_name)
{
    string res = "";
    ifstream file(file_name); //NEED TO ADD EXCEPTION, WHEN NO SUCH FILE

    string tmp = "";
    while (file >> tmp)
        res += tmp + " ";
    file.close();
    return res;
}

ostream& operator <<(ostream& os, const HeightsMap& map)
{
    if (map.isEmpty())
    {
        os << "HeightsMap is empty.";
        return os;
    }

    ConstIterator<height_t> It = map.cbegin();
    while (It != map.cend())
    {
        os << '\n' << '[' << *It++;
        for (int i = 1; i < map.getSize() && It != map.cend(); It++, i++)
            os << "; " << *It ;
        os << ']';
    }
    os << endl;

    return os;
}
