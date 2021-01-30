
#ifndef _POLYGON_
#define _POLYGON_

#include "shape.h"
#include <vector>
#include <initializer_list>
#include <algorithm>

class Polygon : public Shape {
protected: 
	std::vector<Point> vertices;                               // ���������� ������
private:
    double VectComp(Point, Point, Point);
public:
	Polygon(const std::vector<Point>&);
	Polygon(const std::initializer_list<Point>&);

	int verticesCount() const;                                  // ���������� ������
	std::vector<Point> getVertices() const;                     // ������ ������
	bool isConvex() const;                                      // ����������

    double perimeter() const;
    double area() const;

    bool operator==(const Shape&) const;
    bool operator!=(const Shape&) const;
    bool isCongruentTo(const Shape&) const;
    bool isSimilarTo(const Shape&) const;
    bool containsPoint(Point) const;

    void rotate(Point, double);
    void reflex(Point);
    void reflex(Line);
    void scale(Point, double);

    ~Polygon();
};

// ----------------------------------------------------- ������������ ----------------------------------------------

Polygon::Polygon(const std::vector<Point>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        vertices.push_back(vec[i]);
    }
}

Polygon::Polygon(const std::initializer_list<Point>& list) {
    for (auto it : list) {
        vertices.push_back(it);
    }
}

// --------------------------------------------- ������� �������������� ---------------------------------------------

int Polygon::verticesCount() const {
    return vertices.size();
}

std::vector<Point> Polygon::getVertices() const {
    return vertices;
}

double Polygon::VecComp(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p2.y) - (p3.x - p2.x) * (p2.y - p1.y);
}

bool Polygon::isConvex() const {
    size_t i = 0;
    for (; i < vertices.size() - 2; ++i) {
        if (VecComp(vertices[i], vertices[i + 1], vertices[i + 2]) < 0) return false;
    }

    if (vertices[i], vertices[i + 1], vertices[0] < 0) return false;
    if (vertices[i + 1], vertices[0], vertices[1] < 0) return false;

    return true;
}

// ------------------------------------------------- ����� ������� -----------------------------------------------------

double Polygon::perimeter() const {
    double perimeter = 0;
    size_t i = 0;
    for (; i < vertices.size() - 1; ++i) {
        perimeter += sqrt((vertices[i + 1].x - vertices[i].x) * (vertices[i + 1].x - vertices[i].x)
                            + (vertices[i + 1].y - vertices[i].y) * (vertices[i + 1].y - vertices[i].y));
    }

    perimeter += (vertices[0].x - vertices[i].x) * (vertices[0].x - vertices[i].x)
        + (vertices[0].y - vertices[i].y) * (vertices[0].y - vertices[i].y);
    return perimeter;
}

double Polygon::area() const {
    double area = 0;                                                // ������ ������� �� ������� ������
    size_t i = 0;

    for (; i < vertices.size() - 1; ++i) {
        area += vertices[i].x * vertices[i + 1].y;
    }
    area += vertices[i + 1].x * vertices[0].y;

    for (i = 0; i < vertices.size() - 1; ++i) {
        area -= vertices[i].y * vertices[i + 1].x;
    }
    area -= vertices[i + 1].y * vertices[0].x;

    area = abs(area) / 2;
    return area;
}

bool Polygon::operator== (const Shape& figure) const {
    const Polygon f_copy = dynamic_cast<const Polygon&>(figure);
    if (f_copy != nullptr) {
        if (f_copy.verticesCount() != verticesCount()) return false;

        auto it1 = std::find(f_copy.vertices.begin(), f_copy.vertices.end(), vertices[0]);
        auto it2 = std::find(f_copy.vertices.begin(), f_copy.vertices.end(), vertices[1]);
    
        if (it1 == f_copy.vertices.end() || it2 == f_copy.vertices.end() || (abs(it1 - it2) != 1 && abs(it1 - it2) != vertices.size() - 1)) {
           return false;
        }
        
        size_t i = 0;
        if (it1 < it2) {
            for (; it2 != f_copy.vertices.end(); ++it2, ++i) {
                if (vertices[i + 1] != *it2) return false;
            }
            for (it2 = f_copy.vertices.begin(); it2 != it1; ++it2, ++i) {
                if (vertices[i] != *it2) return false;
            }

            return true;
        }
        else {
            for (; it1 != f_copy.vertices.begin(); --it1, ++i) {
                if (vertices[i] != *it1) return false;
            }
            if (vertices[i++] != *it1) return false;
            for (it1 = --f_copy.vertices.end(); it2 != it1; --it1, ++i) {
                if (vertices[i] != *it1) return false;
            }

            return true;
        }
    }

    return false;
}

bool Polygon::operator!= (const Shape& figure) const {
    return !(*this == figure);
}


bool Polygon::isSimilarTo(const Shape&) const {
    const Polygon f_copy = dynamic_cast<const Polygon&>(figure);
    if (f_copy != nullptr) {
        if (f_copy.vertices.size() != vertices.size()) return false;

        double coef_sP = perimeter() / f_copy.perimeter();
        double coef_sS = area() / f_copy.area();
    
        return is_equal(coef_sP * coef_sP, coef_sS);
    }

    return false;
}

#endif
