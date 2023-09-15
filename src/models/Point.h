#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point();
    Point(int x, int y);
    ~Point();

    Point operator+(Point& other);
    Point operator+=(Point& other);
    Point operator-(Point& other);
    Point operator-=(Point& other);
    Point operator*(int scalar);
    Point operator*=(int scalar);
    Point& operator=(const Point& other);
    bool operator==(Point& other);

    // x and y are made public to allow for easy access
    int x;
    int y;
};

#endif
