
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

    virtual vector<Point *> *getAllPossibleStates(Point *myPlace);

    Point *getInition() const {
        return inition;
    }

    void setInition(Point *inition) {
        Searchable::inition = inition;
    }

    Point *getGoal() const {
        return goal;
    }

    void setGoal(Point *goal) {
        Searchable::goal = goal;
    }
};

#endif //NEWPROJ_SEARCHABLE_H
