
#ifndef _CIRCLE_
#define _CIRCLE_

#include "ellipse.h"

class Circle final : public Ellipse {
public:
	Circle(Point, double);						// конструктор от центра и радиуса
	~Circle() = default;
	
	double radius() const;						// получаем радиус круга
};

Circle::Circle(Point center, double radius) {
	Ellipse::focus1 = center;
	Ellipse::focus2 = center;

	Ellipse::sMajorAxis = radius;
}

double Circle::radius() const {
	return sMajorAxis;
}

#endif