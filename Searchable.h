/*****************************
 * Project part B of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * Januar 2019
 ******************************/

#ifndef NEWPROJ_SEARCHABLE_H
#define NEWPROJ_SEARCHABLE_H

#include "Point.h"
#include <vector>

using std::vector;

class Searchable {
protected:
    Point *inition;
    Point *goal;

public:

    virtual vector<Point *> *getAllPossibleStates(Searchable *searchable, Point *myPlace) = 0;

    virtual Point *getInition() const {
        return inition;
    }

    virtual void setInition(Point *inition) {
        Searchable::inition = inition;
    }

    virtual Point *getGoal() const {
        return goal;
    }

    virtual void setGoal(Point *goal) {
        Searchable::goal = goal;
    }
};

#endif //NEWPROJ_SEARCHABLE_H
