
#ifndef _TRIANGLE_
#define _TRIANGLE_

#include "polygon.h"
#include "ellipse_circle.h"

class Trinagle final : public Polygon {
	Square(const Point&, const Point&, const Point&);						// конструктор по трем точкам

	Circle circumscribedCircle() const;										// объект класса круга, описанного вокруг треугольника
	Circle inscribedCircle() const;											// объект класса круга, вписанного в треугольника
	Point centroid() const;													// координаты центра масс
	Point orthocenter() const;												// ортоцентр
	Line EulerLine() const;													// Ёйлерова пр€ма€
	Circle ninePointsCircle() const;										// окружность Ёйлера

	~Triangle() = default;
};

Trinagle::Triangle(const Point& p1, const Point& p2, const Point& p3) :
	Polygon({p1, p2, p3}) {}


#endif