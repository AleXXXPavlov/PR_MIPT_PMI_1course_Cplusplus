
#ifndef _CIRCLE_
#define _CIRCLE_

#include "ellipse.h"

class Circle final : public Ellipse {
public:
	Circle(Point, double);						// ����������� �� ������ � �������
	~Circle() = default;
	
	double radius() const;						// �������� ������ �����
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