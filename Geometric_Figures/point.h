
#ifndef _POINT_
#define _POINT_

#include "equal.h"

typedef struct Point {
    double x = 0;
    double y = 0;

    // ������������ / ����������
    Point() = default;
    Point(double, double);
    ~Point() = default;

    // ��������� ��������� ���� �����
    inline bool operator== (const Point&) const;
    inline bool operator!= (const Point&) const;

} Point;

//---------------------------------------------- ����������� � ����������� -----------------------------------------------------

Point::Point(double x, double y) :
    x(x), y(y) {}

//--------------------------------------------- ������ ��������� ��������� ----------------------------------------------------
inline bool Point::operator== (const Point& obj) const {
    return is_equal(x, obj.x) && is_equal(y, obj.y);
}

inline bool Point::operator!= (const Point& obj) const {
    return !is_equal(x, obj.x) || !is_equal(y, obj.y);
}

#endif