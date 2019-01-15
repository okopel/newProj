#ifndef NEWPROJ_BFS_H
#define NEWPROJ_BFS_H

#include "Searcher.h"
#include <queue>
#include "Point.h"
#include <list>

using std::queue;
using std::list;

class BFS : public Searcher {
public:

    vector<Point *> *search(Searchable *searchable) override {

        queue<Point *> queue;
        // black and grey list
        list<Point *> open;
        list<Point *> close;
        // this is not forest, so we begin from 1 vertex
        queue.push(searchable->getInition());
        close.push_back(queue.front());
        while (!queue.empty()) {
            auto s = queue.front();
            queue.pop();
            // stop condition : return goal
            if (s->equal(searchable->getGoal())) {
                return this->backTrace(searchable->getInition(), s);
            }

            auto adjs = searchable->getAllPossibleStates(searchable, s);
            for (auto adj : *adjs) {
                if (adj == nullptr || adj->getCost() == -1) {
                    continue;
                }
                // mark all states as visited or not
                bool childVisited = false;
                for (auto vertex : close) {
                    if (vertex->equal(adj)) {
                        childVisited = true;
                        break;
                    }
                }
                // set came from
                if (!childVisited) {
                    close.push_back(adj);
                    adj->setCameFrom(s);
                    queue.push(adj);
                }

            }
        }
        return nullptr;//there isnt path
    }
};


#endif //NEWPROJ_BFS_H
