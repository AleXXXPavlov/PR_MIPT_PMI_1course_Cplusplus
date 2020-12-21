
#ifndef _EQUAL_
#define _EQUAL_

// ���������� �������� ��� ���������
const double EPSILON = 1e-8;

// ������� ��� ��������� ����� ���� double
inline bool is_equal(double coord1, double coord2) {
    return abs(coord1 - coord2) < EPSILON;
}

#endif