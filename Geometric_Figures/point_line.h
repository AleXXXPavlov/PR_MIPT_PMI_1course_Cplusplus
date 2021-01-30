
#ifndef _POINT_LINE_
#define _POINT_LINE_

#include "equal.h"

typedef struct Point {
    double x = 0;
    double y = 0;

    // Конструкторы / Деструктор
    Point() = default;
    Point(double, double);
    ~Point() = default;

    // Операторы сравнения двух точек
    inline bool operator== (const Point&) const;
    inline bool operator!= (const Point&) const;

    // Допольнительные функции
    void rotate(Point, double);
    void reflex(Point center);
    void reflex(Line axis);
    void scale(Point, double);

} Point;

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


/* 
// ------------------------------------------------------ Point -----------------------------------------------------------------
*/

// ---------------------------------------------- Конструктор с параметрами -----------------------------------------------------

Point::Point(double x, double y) :
    x(x), y(y) {}

//--------------------------------------------- Булевы операторы сравнения ----------------------------------------------------
inline bool Point::operator== (const Point& obj) const {
    return is_equal(x, obj.x) && is_equal(y, obj.y);
}

inline bool Point::operator!= (const Point& obj) const {
    return !is_equal(x, obj.x) || !is_equal(y, obj.y);
}

// ------------------------------------------------ Дополнительные функции -----------------------------------------------------
void Point::rotate(Point center, double angle) {
    angle *= 180 / (2 * M_PI);

    double new_x = x - center.x;
    double new_y = y - center.y;

    x = center.x + cos(angle) * new_x - sin(angle) * new_y;
    y = center.y + cos(angle) * new_y + sin(angle) * new_x;
}

void Point::reflex(Point center) {
    x = 2 * center.x - x;
    y = 2 * center.y - y;
}

void Point::reflex(Line axis) {
    double num = -(axis.coef_x * x + axis.coef_y * y + axis.coef_f) / (axis.coef_x * axis.coef_x + axis.coef_y * axis.coef_y);
    x += 2 * num * axis.coef_x;
    y += 2 * num * axis.coef_y;
}

void Point::scale(Point center, double coef) {
    double dist_x = center.x - x;
    double dist_y = center.y - y;

    x = center.x - dist_x * coef;
    y = center.y - dist_y * coef;
}


/*
// ------------------------------------------------------ Line -----------------------------------------------------------------
*/

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