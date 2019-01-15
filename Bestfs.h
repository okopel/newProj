

#ifndef NEWPROJ_BESTFS_H
#define NEWPROJ_BESTFS_H

#include "Searcher.h"
#include <functional>
#include <queue>
#include <vector>
#include <string>
#include <stdio.h>
#include <list>

using std::string;
using std::priority_queue;
using std::list;
using std::begin;
using std::end;
using std::cout;
using std::endl;

class Bestfs : public Searcher {

private:
    bool isInOpen(Point state, priority_queue<Point *> open) {
        while (!open.empty()) {
            auto openStae = open.top();
            if (state == openStae) {
                return true;
            }
            open.pop();
        }
        return false;
    }

public:
    vector<Point *> *search(Searchable *searchable) override {
        auto initionl = searchable->getInition();
        auto goal = searchable->getGoal();
        priority_queue<Point *> open;
        open.push(initionl);
        list<Point *> closed;
        while (!open.empty()) {
            auto s = open.top();
            open.pop();
            closed.push_back(s);
            if (s->equal(goal)) {
                return this->backTrace(initionl, s);
            }
            auto *possibleSates = searchable->getAllPossibleStates(searchable, s);
            for (int i = 0; i < possibleSates->size(); i++) {
                if (possibleSates->at(i) == nullptr || possibleSates->at(i)->getCost() == -1) {
                    continue;
                }
                bool isInOpen = false;
                bool isInClose = false;
                for (auto vertex:closed) {
                    if (*vertex == (possibleSates->at(i))) {
                        isInClose = true;
                        break;
                    }
                }
                isInOpen = this->isInOpen(*possibleSates->at(i), open);
                if (!isInClose && !isInOpen) {
                    possibleSates->at(i)->setCameFrom(s);
                    open.push(possibleSates->at(i));
                } else if (isInClose) {
                    continue;
                } else {
                    possibleSates->at(i)->setCameFrom(s);
                    open.push(possibleSates->at(i));
                }
                //todo Otherwise, adjust its priority in OPEN??
            }
        }

        return nullptr;//there is not path
    }
};

#endif //NEWPROJ_BESTFS_H
