
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
        if (goal == nullptr) {
            return nullptr;
        }
        return this->backTrace(searchable->getInition(), goal);
    }

    Point *visit(Point *state, list<Point *> *blacks, list<Point *> *grays, Searchable *searchable) {
        // stop condition
        if (searchable->getGoal() == state) { return state; }
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
                return this->visit(a, blacks, grays, searchable);
            }
        }
        blacks->push_back(state);
    }
};


#endif //NEWPROJ_DFS_H
