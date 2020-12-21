
#ifndef _SHAPE_
#define _SHAPE_

#include "point.h"
#include "line.h"

// Abstract class
class Shape {
public:
    virtual double perimeter() const = 0;
    virtual double area() const = 0;

    virtual bool operator== (const Shape&) const = 0;
    virtual bool operator!= (const Shape&) const = 0;
    virtual bool isCongruentTo(const Shape&) const = 0;
    virtual bool isSimilarTo(const Shape&) const = 0;

    virtual bool containsPoint(Point) const = 0;

    virtual void rotate(Point, double) = 0;
    virtual void reflex(Point) = 0;
    virtual void reflex(Line) = 0;
    virtual void scale(Point, double) = 0;

    virtual ~Shape() = 0;
};



#endif