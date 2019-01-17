/*****************************
 * Project part B of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * Januar 2019
 ******************************/
#ifndef NEWPROJ_DFS_H
#define NEWPROJ_DFS_H

#include "Searcher.h"
#include <list>
#include "Point.h"

using std::list;

class DFS : public Searcher {
public:
    vector<Point *> *search(Searchable *searchable) override {
        // create database
        auto *blacks = new list<Point *>;
        auto *grays = new list<Point *>;
        Point *begin = searchable->getInition();
        Point *goal = this->visit(begin, blacks, grays, searchable);
        if (goal == searchable->getGoal()) {
            cout << "DFS:\n num of points which eq" << this->gettotalCost() << endl;
            return this->backTrace(searchable->getInition(), goal);
        }
        //  delete blacks;
        // delete grays;
        return nullptr;
    }

    Point *visit(Point *state, list<Point *> *blacks, list<Point *> *grays, Searchable *searchable) {
        this->totalCost++;
        // stop condition
        if (searchable->getGoal()->equal(state)) { return state; }
        grays->push_back(state);
        auto *adjs = searchable->getAllPossibleStates(searchable, state);
        for (auto a : *adjs) {
            if (a == nullptr || a->getCost() == -1) {
                continue;
            }
            bool isWhite = true;
            for (auto v:*grays) {
                if (v->equal(a)) {
                    isWhite = false;
                }
            }
            if (isWhite) {
                a->setCameFrom(state);
                Point *tmp = this->visit(a, blacks, grays, searchable);
                if (tmp == searchable->getGoal()) {
                    return tmp;
                }
            }
        }
        blacks->push_back(state);
    }
};


#endif //NEWPROJ_DFS_H
