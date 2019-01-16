/*****************************
 * Project part B of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * Januar 2019
 ******************************/

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

//    bool cmpOfPQueue(map<Point *, int> *gScore, Point *first, Point *second) {
//        return gScore->at(first) < gScore->at(second);
//    }


public:
//    class gPoint {
//        Point *p;
//        int gscore;
//    public:
//        gPoint(Point *p) : p(p), gscore(INTMAX_MAX - 1) {}
//
//        int getGscore() {
//            return gscore;
//        }
//
//        void setGscore(int gscore) {
//            gPoint::gscore = gscore;
//        }
//
//        int getFscore() {
//            return p->getCost();
//        }
//
//        Point *getP() const {
//            return p;
//        }
//
//        void setCameFrom(Point *p) {
//            this->p->setCameFrom(p);
//        }
//
//        Point *getCameFrom() {
//            return this->p->getCameFrom();
//        }
//    };

    vector<Point *> *search(Searchable *searchable) override {
        list<Point *> close;
        // TODO: according fscore value

        //auto cmp = [](gPoint *p1, gPoint *p2) { return p1->getFscore() < p2->getFscore(); };
        priority_queue<Point *> open;


        open.push(searchable->getInition());
        // initialize heuristic cost as -1

//        for (auto point : gScore) {
//            auto p = point.first;
//            gScore.at(p) = INTMAX_MAX - 1;
//        }
        // this is not forest, so we begin from 1 vertex
        //  gScore[searchable->getInition()] = 0;
        map<Point *, int> fScore;
        map<Point *, int> gScore;
        for (auto point : fScore) {
            auto p = point.first;
            gScore.at(p) = 999999;
        }
        fScore[searchable->getInition()] = this->heuristicCost(searchable->getInition(), searchable->getGoal());
        while (!open.empty()) {

            auto current = open.top();
            open.pop();
            // stop contition : return goal
            if (current == searchable->getGoal()) {
                return this->backTrace(searchable->getInition(), searchable->getGoal());
            }
            open.pop();
            close.push_back(current);
            vector<Point *> *adjs = searchable->getAllPossibleStates(searchable, current);
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
                if (!inClose) {
                    continue;
                }
                int tentative_gScore = gScore[current] + current->getCost();
                bool adjInOpen = this->isInOpen(*adj, open);
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
        return nullptr;
    }
};


#endif //NEWPROJ_ASTAR_H
