
#ifndef _LINE_
#define _LINE_

#include "equal.h"

typedef struct Line {
    double ang_coef = 0;
    double shift = 0;

    // Constructors // Destructor
    Line() = default;
    Line(double, double);                               // angular_coefficient, shift
    Line(const Point&, const Point&);                   // two different points
    Line(const Point&, double);                         // point, angular_coefficient
    ~Line() = default;

    // Comparasion operations
    inline bool operator== (const Line&) const;
    inline bool operator!= (const Line&) const;

} Line;

// -------------------------------------------------- Constructors --------------------------------------------------

Line::Line(double ang_coef, double shift) :
    ang_coef(ang_coef), shift(shift) {}

Line::Line(const Point& point1, const Point& point2) {
    if (point1.y > point2.y) {
        ang_coef = (point1.y - point2.y) / (point1.x - point2.x);
        shift = point1.y - ang_coef * point1.x;
    }
    else {
        ang_coef = (point2.y - point1.y) / (point2.x - point1.x);
        shift = point1.y - ang_coef * point1.x;
    }
}

Line::Line(const Point& point, double ang_coef) :
    ang_coef(ang_coef)
{
    shift = point.y - ang_coef * point.x;
}

// ------------------------------------------- Bool Comparasion Operations -----------------------------------------

inline bool Line::operator== (const Line& obj) const {
    return is_equal(ang_coef, obj.ang_coef) && is_equal(shift, obj.shift);
}

inline bool Line::operator!= (const Line& obj) const {
    return !is_equal(ang_coef, obj.ang_coef) || !is_equal(shift, obj.shift);
}


#endif