#include <iostream>
#include <cassert>
#include "rectangleType.h"

using namespace std;

void rectangleType::setDimension(double l, double w)
{
    if (l >= 0)
      len = l;
    else
      len = 0;

    if (w >= 0)
      wid = w;
    else
      wid = 0;
}

double rectangleType::getLen() const
{
    return len;
}

double rectangleType::getWid()const
{
    return wid;
}

double rectangleType::area() const
{
    return len * wid;
}

double rectangleType::perimeter() const
{
    return 2 * (len + wid);
}

rectangleType::rectangleType(double l, double w)
{
    setDimension(l, w);
}

rectangleType::rectangleType()
{
    len = 0;
    wid = 0;
}

rectangleType rectangleType::operator ++ ()
{
    rectangleType r;
    r.len = ++len;
    r.wid = ++wid;
    return r;
}

rectangleType rectangleType::operator ++ (int u)
{
    rectangleType r;
    r.len = len++;
    r.wid = wid++;
    return r;
}

rectangleType rectangleType::operator -- ()
{
    if(len > 0 && wid > 0)
    {
        rectangleType r;
        r.len = --len;
        r.wid = --wid;
        return r;
    }
    else
    {
        cout<<"Not Possible\n";
        rectangleType r;
        r.len = 0;
        r.wid = 0;
        return r;
    }
}

rectangleType rectangleType::operator -- (int u)
{
    if(len > 0 && wid > 0)
    {
        rectangleType r;
        r.len = len--;
        r.wid = wid--;
        return r;
    }
    else 
    {
        cout<<"Not Possible\n";
        rectangleType r;
        r.len = 0;
        r.wid = 0;
        return r;
    }
}

rectangleType rectangleType::operator + (const rectangleType& rectangle) const
{
    rectangleType r;
    r.len = len + rectangle.len;
    r.wid = wid + rectangle.wid;
    return r;
}

rectangleType rectangleType::operator - (const rectangleType& rectangle) const
{
    if(len >= rectangle.len && wid >= rectangle.wid)
    {
        rectangleType r;
        r.len = len - rectangle.len;
        r.wid = wid - rectangle.wid;
        return r;
    }
    else
    {
        cout<<"Not Possible\n";
        rectangleType r;
        r.len = 0;
        r.wid = 0;
        return r;
    }
}
rectangleType rectangleType::operator * (const rectangleType& rectangle) const
{
    rectangleType r;
    r.len = len * rectangle.len;
    r.wid = wid * rectangle.wid;
    return r;
}

bool rectangleType::operator == (const rectangleType & rectangle) const
{
    return this->area() == rectangle.area();
}

bool rectangleType::operator != (const rectangleType& rectangle) const
{
    return this->area() != rectangle.area();
}

bool rectangleType::operator <= (const rectangleType& rectangle) const
{
    return this->area() <= rectangle.area();
}

bool rectangleType::operator < (const rectangleType& rectangle) const
{
    return this->area() < rectangle.area();
}

bool rectangleType::operator >= (const rectangleType& rectangle) const
{
    return this->area() >= rectangle.area();
}

bool rectangleType::operator > (const rectangleType& rectangle) const
{
    return this->area() > rectangle.area();
}

ostream& operator << (ostream& osObject, const rectangleType& rectangle)
{
    osObject << "Len = " << rectangle.len << "; wid = " << rectangle.wid;

    return osObject;
}

istream& operator >> (istream& isObject, rectangleType& rectangle)
{
    isObject >> rectangle.len >> rectangle.wid;

    return isObject;
}
