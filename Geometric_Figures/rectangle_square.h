
#ifndef _RECTANGLE_SQUARE_
#define _RECTANGLE_SQUARE_

#include "polygon.h"
#include "ellipse_circle.h"

class Rectangle : public Polygon {
public:
	Rectangle(const Point&, const Point&, double);							// по двум противоположным точкам и отношению сторон	

	Point center() const;													// центр пересечения диагоналей
	std::pair<Line, Line> diagonals() const;								// пара диагоналей

	~Rectangle() = default;
};

class Square final : public Rectangle {
	Square(const Point&, const Point&);										// конструктор по двум противоположным точкам
																					
	Circle circumscribedCircle() const;										// объект класса круга, описанного вокруг квадрата
	Circle inscribedCircle() const;											// объект класса круга, вписанного в квадрат

	~Square = default;
};

/*
// ------------------------------------------------------ Rectangle -----------------------------------------------------------------
*/

Rectangle::Rectangle(const Point& p1, const Point& p3, double ratio) {
	if (ratio > 1) ratio = 1 / ratio;

	double diagLength = sqrt((p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y));
	double bigSideLength = sqrt(diagLength * diagLength / (1 + ratio *  ratio));
	double smallSideLength = bigSideLength * ratio;

	double sn_1 = 2 * bigSideLength / diagLength * smallSideLength / diagLength;
	double cs_1 = -(2 * (smallSideLength / diagLength) * (smallSideLength / diagLength) - 1);
	double sn_2 = 2 * smallSideLength / diagLength * smallSideLength / diagLength;
	double cs_2 = 2 * (smallSideLength / diagLength) * (smallSideLength / diagLength) - 1;

	Point p2, p4;
	p2.x = p1.y > p3.y ? p1.x * cs_2 - p1.y * sn_2 : p3.x * cs_2 - p3.y * sn_2;
	p2.y = p1.y > p3.y ? p1.x * sn_2 + p1.y * cs_2 : p3.x * sn_2 + p3.y * cs_2;

	p4.x = p1.y > p3.y ? p1.x * cs_1 - p1.y * sn_1 : p3.x * cs_1 - p3.y * sn_1;
	p4.y = p1.y > p3.y ? p1.x * sn_1 + p1.y * cs_1 : p3.x * sn_1 + p3.y * cs_1;
	
	vertices.push_back(p1);
	vertices.push_back(p2);
	vertices.push_back(p3);
	vertices.push_back(p4);
}

Point Rectangle::center() const {
	double coordX = (vertices[0].x + vertices[2].x) / 2;
	double coordY = (vertices[0].y + vertices[2].y) / 2;

	return Point(coordX, coordY);
}

std::pair<Line, Line> Rectangle::diagonals() const {
	Line diag1(vertices[0], vertices[2]);
	Line diag2(vertices[1], vertices[3]);

	return std::pair<Line, Line>(diag1, diag2);
}

/*
// --------------------------------------------------------- Square --------------------------------------------------------------------
*/

Square::Square(const Point& p1, const Point& p3) :
	Rectangle(p1, p3, 1) {}

Circle Square::circumscribedCircle() const {
	double radius = sqrt((vertices[0].x - vertices[2].x) * (vertices[0].x - vertices[2].x) +
		(vertices[0].y - vertices[2].y) * (vertices[0].y - vertices[2].y)) / 2;
	Point center((vertices[0].x + vertices[2].x) / 2, (vertices[0].y + vertices[2].y) / 2);

	return Circle(center, radius);
}

Circle Square::inscribedCircle() const {
	double radius = sqrt((vertices[0].x - vertices[1].x) * (vertices[0].x - vertices[1].x) +
		(vertices[0].y - vertices[1].y) * (vertices[0].y - vertices[1].y)) / 2;
	Point center((vertices[0].x + vertices[2].x) / 2, (vertices[0].y + vertices[2].y) / 2);

	return Circle(center, radius);
}

#endif
