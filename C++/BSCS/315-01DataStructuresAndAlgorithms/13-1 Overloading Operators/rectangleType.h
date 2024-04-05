#ifndef H_rectangleType
#define H_rectangleType

#include <iostream>

using namespace std;

class rectangleType
{
        friend ostream& operator << (ostream&, const rectangleType&);
        friend istream& operator >> (istream&, rectangleType&);

    public:
        void setDimension(double l, double w);
        double getLen() const;
        double getWid() const;
        double area() const;
        double perimeter() const;

        rectangleType operator + (const rectangleType&) const;
        rectangleType operator - (const rectangleType&) const;
        rectangleType operator * (const rectangleType&) const;

        rectangleType operator ++ ();
        rectangleType operator ++ (int);
        rectangleType operator -- ();
        rectangleType operator -- (int);

        bool operator < (const rectangleType&) const;
        bool operator > (const rectangleType&) const;
        bool operator <= (const rectangleType&) const;
        bool operator >= (const rectangleType&) const;
        bool operator == (const rectangleType&) const;
        bool operator != (const rectangleType&) const;

        rectangleType();
        rectangleType(double l, double w);

    protected:
        double len;
        double wid;
};

#endif
