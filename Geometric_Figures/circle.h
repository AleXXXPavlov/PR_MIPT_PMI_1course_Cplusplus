
#ifndef _CIRCLE_
#define _CIRCLE_

#include "ellipse.h"

class Circle final : public Ellipse {
public:
	Circle(Point, double);						// êîíñòðóêòîð îò öåíòðà è ðàäèóñà
	~Circle() = default;
	
	double radius() const;						// ïîëó÷àåì ðàäèóñ êðóãà
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
