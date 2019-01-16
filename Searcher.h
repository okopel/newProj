/*****************************
 * Project part B of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * Januar 2019
 ******************************/

#ifndef NEWPROJ_SEARCHER_H
#define NEWPROJ_SEARCHER_H

#include "Searchable.h"
#include <vector>
#include "Point.h"

using std::vector;

class Searcher {
protected:
    vector<Point *> *backTrace(Point *initionl, Point *goal) {
        auto vector = new ::vector<Point *>;
        vector->push_back(goal);
        auto point = goal->getCameFrom();
        while (point != nullptr) {
            vector->push_back(point);
            point = point->getCameFrom();
        }
        return vector;

    }

public:

    virtual vector<Point *> *search(Searchable *searchable) = 0;
};

#endif //NEWPROJ_SEARCHER_H
