
#ifndef NEWPROJ_SOLVER_H
#define NEWPROJ_SOLVER_H

template<class ProblemType, class SolutionType>
class Solver {

    virtual SolutionType solve(ProblemType problem) = 0;
};

#endif //NEWPROJ_SOLVER_H
