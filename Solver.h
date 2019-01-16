/*****************************
 * Project part B of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * Januar 2019
 ******************************/

#ifndef NEWPROJ_SOLVER_H
#define NEWPROJ_SOLVER_H

template<class ProblemType, class SolutionType>
class Solver {
public:
    virtual SolutionType solve(ProblemType problem) = 0;
};

#endif //NEWPROJ_SOLVER_H
