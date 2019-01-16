
#ifndef NEWPROJ_MYASTAR_H
#define NEWPROJ_MYASTAR_H

#include "Searcher.h"
#include <math.h>
#include "Point.h"
#include <list>
#include <queue>
#include <map>

using std::map;
using std::list;
using std::priority_queue;

class myAStar : public Searcher {
private:
    int heuristicCost(Point *current, Point *goal) {
        int x = current->getX() - goal->getX();
        int y = current->getX() - goal->getX();

        return (int) sqrt((x * x) + (y * y));
    }

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
        list<Point *> close;
        priority_queue<Point *> open;
        open.push(searchable->getInition());
        searchable->getInition()->costPlus(this->heuristicCost(searchable->getInition(), searchable->getGoal()));
        while (!open.empty()) {
            auto current = open.top();
            open.pop();
            // stop contition : return goal
            if (current->equal(searchable->getGoal())) {
                return this->backTrace(searchable->getInition(), searchable->getGoal());
            }
            // open.pop();
            close.push_back(current);
            auto adjs = searchable->getAllPossibleStates(searchable, current);
            for (auto adj : *adjs) {
                if (adj == nullptr || adj->getCost() == -1) {
                    continue;
                }
                // mark all states as visited or not
                bool inClose = false;
                for (auto &vertex : close) {
                    if (*vertex == adj) {
                        inClose = true;
                        break;
                    }
                }
                // Ignore the neighbor which is already evaluated
                if (inClose) {
                    continue;
                }
                int tentative_gScore = current->getCost();//gScore[current] +cost
                bool adjInOpen = this->isInOpen(*adj, open);
                if (!adjInOpen) { // Discover a new node
                    open.push(adj);
                } else if (tentative_gScore >= adj->getCost()) {
                    continue;
                }
                // This path is the best until now. Record it!
                adj->setCameFrom(current);
                adj->costPlus(heuristicCost(adj, searchable->getGoal()));
            }
        }
        return nullptr;
    }
};


#endif //NEWPROJ_MYASTAR_H
