/*****************************
 * Project part B of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * Januar 2019
 ******************************/

#ifndef NEWPROJ_POINT_H
#define NEWPROJ_POINT_H

#include "State.h"
#include <stdio.h>
#include <iostream>

using std::ostream;
using std::to_string;
using std::string;
using std::cout;
using std::endl;

class Point : public State<int> {
    int x;
    int y;
    // int cost;
    Point *cameFrom;

public:
    Point(int x, int y, int cost) : State(cost), x(x), y(y) {
        State::cameFrom = nullptr;
        this->cameFrom = nullptr;
    }

    Point *getCameFrom() const {
        return cameFrom;
    }

    void setCameFrom(Point *cameFrom) {
        Point::cameFrom = cameFrom;
        State::cameFrom = cameFrom;
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
        return State::state;
    }

    void setCost(int cost) {
        State::setState(cost);
    }

    string printIndex() {
        return "(" + to_string(this->x) + "," + to_string(this->y) + ")";
    }

    string print() {
        return to_string(this->getCost());
    }

    void costPlus(int num) {
        State::setState(this->getCost() + num);
    }

    void costMinus(int num) {
        State::setState(this->getCost() - num);
    }
};

#endif //NEWPROJ_POINT_H
