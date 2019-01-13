
#ifndef NEWPROJ_SEARCHER_H
#define NEWPROJ_SEARCHER_H

#include "Searchable.h"

class Searcher {
protected:
    vector<Point *> *backTrace(Point *initionl, Point *goal) {
        return nullptr;//todo
    }

public:

    virtual vector<Point *> *search(Searchable *searchable) = 0;
};

#endif //NEWPROJ_SEARCHER_H
