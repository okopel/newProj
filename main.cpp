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
#include "BFS.h"
#include "DFS.h"
#include "Astar.h"
#include "myAstar.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::istream;
using std::ofstream;
using std::ostream;

namespace boot {

    int main(int argc, char **argv) {
        CashManager *cm = new FileCacheManager("db.txt");

        auto searchers = new vector<Searcher *>;
        searchers->push_back(new BFS());
        searchers->push_back(new DFS());
        searchers->push_back(new myAStar());
        searchers->push_back(new Bestfs());

        for (auto iter: *searchers) {
            Solver<Searchable *, vector<Point *> *> *solver = new SolveSearchAdapter(iter);
            ClientHandler<Searchable *, vector<Point *> *> *clientHandler = new MyMatrixClient(solver, cm);
            clientHandler->handleClient(argv[1], argv[2]);
            delete clientHandler;
        }
        for (auto iter: *searchers) {
            delete iter;
        }
        delete (cm);
        cout << "GOOS JOB" << endl;
    }
};

int main(int argc, char **argv) {
    boot::main(argc, argv);
    return 0;
};