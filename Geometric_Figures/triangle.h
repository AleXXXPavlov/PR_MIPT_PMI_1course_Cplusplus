
#ifndef _TRIANGLE_
#define _TRIANGLE_

#include "polygon.h"
#include "ellipse_circle.h"

class Trinagle final : public Polygon {
	Square(const Point&, const Point&, const Point&);						// ����������� �� ���� ������

	Circle circumscribedCircle() const;										// ������ ������ �����, ���������� ������ ������������
	Circle inscribedCircle() const;											// ������ ������ �����, ���������� � ������������
	Point centroid() const;													// ���������� ������ ����
	Point orthocenter() const;												// ���������
	Line EulerLine() const;													// �������� ������
	Circle ninePointsCircle() const;										// ���������� ������

	~Triangle() = default;
};

Trinagle::Triangle(const Point& p1, const Point& p2, const Point& p3) :
	Polygon({p1, p2, p3}) {}


#endif