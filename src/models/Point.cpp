#include "Point.h"

Point::Point() { }

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point::~Point() { }

Point Point::operator+(Point& other) {
    return Point(this->x + other.x, this->y + other.y);
}

Point Point::operator+=(Point& other) {
    this->x += other.x;
    this->y += other.y;

    return *this;
}

Point Point::operator-(Point& other) {
    return Point(this->x - other.x, this->y - other.y);
}

Point Point::operator-=(Point& other) {
    this->x -= other.x;
    this->y -= other.y;

    return *this;
}

Point Point::operator*(int scalar) {
    return Point(this->x * scalar, this->y * scalar);
}

Point Point::operator*=(int scalar) {
    this->x *= scalar;
    this->y *= scalar;

    return *this;
}

Point& Point::operator=(const Point& other) {
    if (this != &other) { // Check for self-assignment
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

bool Point::operator==(Point& other) {
    return this->x == other.x && this->y == other.y;
}
