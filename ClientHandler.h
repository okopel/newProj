

#ifndef NEWPROJ_CLIENTHANDLER_H
#define NEWPROJ_CLIENTHANDLER_H

#include "Solver.h"
#include "CashManager.h"

template<class ProblemType, class SolutionType>
class ClientHandler {
protected:
    Solver<ProblemType, SolutionType> *solver;
    CashManager *cashManager;

public:
    ClientHandler() {}

    ClientHandler(Solver<ProblemType, SolutionType> *solver, CashManager *cashManager) : solver(solver),
                                                                                         cashManager(cashManager) {}

    virtual void handleClient(string inputFile, string outputFile) = 0;
};

#endif //NEWPROJ_CLIENTHANDLER_H
