

#ifndef NEWPROJ_POINT_H
#define NEWPROJ_POINT_H

#include "State.h"

using std::ostream;
using std::to_string;

class Point : public State<int> {
    int x;
    int y;
    int cost;
    Point *cameFrom;

public:
    Point(int x, int y, int cost) : x(x), y(y), cost(cost) {
        cameFrom = nullptr;
    }

    Point *getCameFrom() const {
        return cameFrom;
    }

    void setCameFrom(Point *cameFrom) {
        Point::cameFrom = cameFrom;
    }

    bool equal(Point *other) {
        if (other == nullptr) {
            return false;
        }
        return this->operator==(other);
    }

    bool operator==(Point *other) {
        if (other == nullptr) {
            return false;
        }
        return this->operator==(*other);
    }

    bool operator==(Point other) {
        return (this->x == other.getX()) && (this->y == other.getY());
    }

    int getX() const {
        return x;
    }

    void setX(int x) {
        Point::x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        Point::y = y;
    }

    int getCost() const {
        return cost;
    }

    void setCost(int cost) {
        Point::cost = cost;
    }

    string printIndex() {
        return "(" + to_string(this->x) + "," + to_string(this->y) + ")";
    }

    string print() {
        return to_string(this->getCost());
    }

    void costPlus(int num) {
        this->cost += num;
    }

    void costMinus(int num) {
        this->cost -= num;
    }
};

#endif //NEWPROJ_POINT_H
