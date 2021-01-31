
#ifndef _SHAPE_
#define _SHAPE_

#include "point_line.h"

// Abstract class of figures
class Shape {
public:
    virtual double perimeter() const = 0;
    virtual double area() const = 0;

    virtual bool operator== (const Shape&) const = 0;
    virtual bool operator!= (const Shape&) const = 0;                                 
    virtual bool isCongruentTo(const Shape&) const = 0;                                // можно ли их совместить движением плоскости
    virtual bool isSimilarTo(const Shape&) const = 0;                                  // подобны ли фигуры
    virtual bool containsPoint(Point) const = 0;                                       // лежит ли точка внутри фигуры

    virtual void rotate(Point, double) = 0;                                            // поворот относительно некоторой точки с заданным углом
    virtual void reflex(Point) = 0;
    virtual void reflex(Line) = 0;
    virtual void scale(Point, double) = 0;

    virtual ~Shape() = 0;
};



#endif