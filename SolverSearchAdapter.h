

#ifndef NEWPROJ_SOLVERSEARCHADAPTER_H
#define NEWPROJ_SOLVERSEARCHADAPTER_H

#include "Solver.h"
#include "Searchable.h"
#include "Point.h"
#include <vector>
#include "Searcher.h"
#include "Matrix.h"

using std::vector;

class SolveSearchAdapter : public Solver<Searchable *, vector<Point *> *> {
    Searcher *searcher;

public:
    SolveSearchAdapter(Searcher *searcher) : Solver(), searcher(searcher) {}

    vector<Point *> *solve(Searchable *problem) override {
        return searcher->search(problem);
    }

};

#endif //NEWPROJ_SOLVERSEARCHADAPTER_H
