
#ifndef NEWPROJ_ASTAR_H
#define NEWPROJ_ASTAR_H


#include "Searcher.h"
#include <math.h>
#include "Point.h"
#include <list>
#include <queue>
#include <map>

using std::map;
using std::list;
using std::priority_queue;

class AStar : public Searcher {
private:
    int heuristicCost(Point *current, Point *goal) {
        int x = current->getX() - goal->getX();
        int y = current->getX() - goal->getX();

        return (int) sqrt((x * x) + (y * y));
    }

public:
    vector<Point *> *search(Searchable *searchable) override {
        list<Point *> close;
        // TODO: according fscore value
        priority_queue<Point *> open;
        open.push(searchable->getInition());
        // initialize heuristic cost as -1

        map<Point *, int> gScore;
        for (auto *point : gScore) {//todo iterator to map
            gScore[point] = -1;
        }
        // this is not forest, so we begin from 1 vertex
        gScore[searchable->getInition()] = 0;
        map<Point *, int> fScore;
        for (auto *point : fScore) {//todo any value to inf
            gScore.at(point) = -1;

        }
        fScore[searchable->getInition()] = this->heuristicCost(searchable->getInition(), searchable->getGoal());
        while (!open.empty()) {

            Point *current = open.top();
            open.pop();
            // stop contition : return goal
            if (current == searchable->getGoal()) {
                return this->backTrace(searchable->getInition(), searchable->getGoal());
            }
            open.pop();
            close.push_back(current);
            vector<Point *> adjs = searchable->getAllPossibleStates(current);
            for (auto adj : adjs) {
                // mark all states as visited or not
                bool inClose = false;
                for (auto &vertex : close) {
                    if (*vertex == adj) {
                        inClose = true;
                        break;
                    }
                }
                // Ignore the neighbor which is already evaluated
                if (!inClose) {
                    continue;
                }
                int tentative_gScore = gScore[current] + current->getCost();
                bool adjInOpen = false;
                for (auto o: open) {//iterator to prioruty queue
                    if (o == adj) {
                        adjInOpen = true;
                        break;
                    }
                }
                if (adjInOpen) { // Discover a new node
                    open.push(adj);
                } else if (tentative_gScore >= gScore.at(adj)) {

                    continue;
                }

                // This path is the best until now. Record it!
                adj->setCameFrom(current);
                gScore[adj] = tentative_gScore;
                fScore[adj] = gScore[adj] + heuristicCost(adj, searchable->getGoal());
            }
        }
    }

};


#endif //NEWPROJ_ASTAR_H
