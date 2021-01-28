
#ifndef _LINE_
#define _LINE_

#include "equal.h"
#include "point.h"

typedef struct Line {
    double coef_y = 0;
    double coef_x = 0;
    double coef_f = 0;

    // Constructors // Destructor
    Line() = default;
    Line(double, double, double);                       // coefficients
    Line(double, double);                               // ang_coef, shift
    Line(const Point&, const Point&);                   // two different points
    Line(const Point&, double);                         // point, angular_coefficient
    ~Line() = default;

    // Comparasion operations
    bool operator== (const Line&) const;
    bool operator!= (const Line&) const;

} Line;

// -------------------------------------------------- Constructors --------------------------------------------------
Line::Line(double coef_y, double coef_x, double coef_f) :
    coef_y(coef_y), coef_x(coef_x), coef_f(coef_f) {}

Line::Line(double ang_coef, double shift) :
    coef_x(-ang_coef), coef_y(1), coef_f(-shift) {}

Line::Line(const Point& point1, const Point& point2) {
    coef_x = point1.y - point2.y;
    coef_y = point2.x - point1.x;
    coef_f = point2.x * point1.y - point2.y * point1.x;
}

Line::Line(const Point& point, double ang_coef) {
    coef_x = -ang_coef;
    coef_y = 1;
    coef_f = ang_coef * point.x - point.y;
}

// ------------------------------------------- Bool Comparasion Operations -----------------------------------------

bool Line::operator== (const Line& obj) const {
    if ((is_equal(coef_x, 0) && !is_equal(obj.coef_x, 0)) || (!is_equal(coef_x, 0) && is_equal(obj.coef_x, 0))) return false;
    if ((is_equal(coef_y, 0) && !is_equal(obj.coef_y, 0)) || (!is_equal(coef_y, 0) && is_equal(obj.coef_y, 0))) return false;
    if ((is_equal(coef_f, 0) && !is_equal(obj.coef_f, 0)) || (!is_equal(coef_f, 0) && is_equal(obj.coef_f, 0))) return false;

    double pp = coef_x / obj.coef_x;
    return is_equal(coef_y, pp * obj.coef_y) && (is_equal(coef_f, pp * obj.coef_f));
}

bool Line::operator!= (const Line& obj) const {
    return !(*this == obj);
}

#endif