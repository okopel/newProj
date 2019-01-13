#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "CashManager.h"
#include "Solver.h"
#include "FileCacheManager.h"
#include "Bestfs.h"
#include "SolverSearchAdapter.h"
#include "ClientHandler.h"
#include "MyMatrixClientHandler.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::istream;
using std::ofstream;
using std::ostream;

namespace boot {

    int main(int argc, char **argv) {
        CashManager *cm = new FileCacheManager(argv[1], argv[2]);
        Solver<Searchable *, vector<Point *> *> *solver = new SolveSearchAdapter(new Bestfs());
        ClientHandler<Searchable *, vector<Point *> *> *clientHandler = new MyMatrixClient(solver, cm);


    }

};

int main(int argc, char **argv) {
    boot::main(argc, argv);
    return 0;
};