
#ifndef _ELLIPSE_
#define _ELLIPSE_

#include "shape.h"
#include <utility>

class Ellipse : public Shape {
public:
    Point focus1;                                       // передний фокус
    Point focus2;                                       // задний фокус
    double sMajorAxis;                                  // большая полуось эллипса

    Ellipse(const Point&, const Point&, double);

    std::pair<Point, Point>   focuses() const;          // получение координат фокусов
    std::pair<Line, Line> directrices() const;          // получение директрис
    double eccentricity() const;                        // получение эксцентриситета
    Point center() const;                               // получение координат центра

    double perimeter() const;
    double area() const;

    bool operator== (const Shape&) const;
    bool operator!= (const Shape&) const;
    bool isCongruentTo(const Shape&) const;
    bool isSimilarTo(const Shape&) const;

    bool containsPoint(Point) const;

    void rotate(Point, double);
    void reflex(Point);
    void reflex(Line);
    void scale(Point, double);
};

// ---------------------------------------- Конструктор ------------------------------------------------
Ellipse::Ellipse(const Point& f1, const Point& f2, double sMA) {
    focus1(f1.x, f1.y);
    focus2(f2.x, f2.y);
    sMajorAxis(sMA);
}

// ---------------------------------------- Общие функции ----------------------------------------------

double Ellipse::perimeter() {
    double sMinorAxis = sqrt(sMajorAxis * sMajorAxis * (1 - eccentricity() * eccentricity()));
    return M_PI * (3 * (sMinorAxis * sMajorAxis) - sqrt((3 * sMinorAxis + sMajorAxis) * (3 * sMajorAxis + sMinorAxis)));
}

double Ellipse::area() {
    double sMinorAxis = sqrt(sMajorAxis * sMajorAxis * (1 - eccentricity() * eccentricity()));
    return M_PI * sMinorAxis * sMajorAxis;
}

bool Ellipse::operator== (const Shape& figure) const {
    const Ellipse f_copy = dynamic_cast<const Ellipse&>(figure);
    if (f_copy != nullptr) {
        return is_equal(f_copy.focus1.x, focus1.x) && is_equal(f_copy.focus1.y, focus1.y)
            && is_equal(f_copy.focus2.x, focus2.x) && is_equal(f_copy.focus2.y, focus2.y) && is_equal(f_copy.sMajorAxis, sMajorAxis);
    }
    return false;
}

bool Ellipse::operator!= (const Shape& figure) const {
    return !(*this == figure);
}

bool Ellipse::isCongruentTo(const Shape& figure) const {
    const Ellipse f_copy = dynamic_cast<const Ellipse&>(figure);
    if (f_copy != nullptr) {
        return is_equal(eccentricity(), f_copy.eccentricity()) && is_equal(sMajorAxis, f_copy.sMajorAxis);
    }
    return false;
}

bool Ellipse::isSimilarTo(const Shape& figure) const {
    const Ellipse f_copy = dynamic_cast<const Ellipse&>(figure);
    if (f_copy != nullptr) {
        return is_equal(eccentricity(), f_copy.eccentricity());
    }
    return false;
}

bool Ellipse::containsPoint(Point pt) const {
    double dist1 = sqrt((focus1.x - pt.x) * (focus1.x - pt.x) + (focus1.y - pt.y) * (focus1.y - pt.y));
    double dist2 = sqrt((focus2.x - pt.x) * (focus2.x - pt.x) + (focus2.y - pt.y) * (focus2.y - pt.y));

    return (dist1 + dist2 < 2 * sMajorAxis || is_equal(dist1 + dist2, 2 * sMajorAxis));
}




// --------------------------------------- Функции эллипса ---------------------------------------------
std::pair<Point, Point> Ellipses::focuses() const {
    return std::pair<Point, Point> (focus1, focus2);
}

double Ellipse::eccentricity() const {
    double ecc = sqrt((focus1.x - focus2.x) * (focus1.x - focus2.x) + (focus1.y - focus2.y) * (focus1.y - focus2.y));
    return ecc / (2 * sMajorAxis);
}

std::pair<Line, Line> Ellipses::directrices() const {
    double ecc = eccentricity();

    Line dir1(1, 0, -sMajorAxis / ecc);
    Line dir2(1, 0,  sMajorAxis / ecc);
    return std::pair<Line, Line>(dir1, dir2);
}

Point Ellipses::center() const {
    Point center((focus1.x + focus2.x) / 2, (focus1.y + focus2.y) / 2);
    return center;
}

#endif