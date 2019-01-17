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
#include <stdio.h>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

class Searcher {
protected:
    int totalCost;

public:
    Searcher() : totalCost(0) {}

protected:
    vector<Point *> *backTrace(Point *initionl, Point *goal) {
        int costOfPath = 0;
        auto vector = new ::vector<Point *>;
        vector->push_back(goal);
        costOfPath += goal->getCost();
        auto point = goal->getCameFrom();
        while (point != nullptr) {
            costOfPath += point->getCost();
            vector->push_back(point);
            point = point->getCameFrom();
        }
        cout << "total cost of path:" << costOfPath << endl;
        return vector;

    }

public:

    virtual vector<Point *> *search(Searchable *searchable) = 0;

    int gettotalCost() {
        return this->totalCost;
    }
};

#endif //NEWPROJ_SEARCHER_H
