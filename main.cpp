/*****************************
 * Project part B of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * Januar 2019
 ******************************/
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
#include "ReadFromFile.h"
#include "Server.h"
#include "StringReverseHandler.h"
#include "StringReverseClientHandler.h"
#include "Servers.h"

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
        Solver<Searchable *, vector<Point *> *> *solver = new SolveSearchAdapter(new BFS());
        ClientHandler<Searchable *, vector<Point *> *> *clientHandler = new MyMatrixClient(solver, cm);
        auto server = new MyParallelServer<Searchable *, vector<Point *> *>();
        server->start(5800, clientHandler);
    }


    int mainv(int argc, char **argv) {
        CashManager *cm = new FileCacheManager("db.txt");
        auto searchers = new vector<Searcher *>;
        searchers->push_back(new myAStar());
        searchers->push_back(new DFS());
        searchers->push_back(new BFS());
//        searchers->push_back(new Bestfs());

        for (auto iter: *searchers) {
            Solver<Searchable *, vector<Point *> *> *solver = new SolveSearchAdapter(iter);
            ClientHandler<Searchable *, vector<Point *> *> *clientHandler = new MyMatrixClient(solver, cm);
            ReadFromFile fromFile(argv[1]);
            string prob = fromFile.getStringOfMatrix();
            string solu;
            clientHandler->handleClient(prob, solu);
            cout << solu << endl;
            delete clientHandler;
        }
        for (auto iter: *searchers) {
            delete iter;

        }
        delete cm;
        cout << "GOOD JOB" << endl;
    }

    int mainc(int argc, char **argv) {
        CashManager *cm = new FileCacheManager("Hello.txt");
        auto sReverst = new StringReverserHandler();
        auto cli = new StringReverseClientHandler(sReverst, cm);
        Server<string, string> *s = new MyParallelServer<string, string>();
        s->start(5800, cli);


    }
};

#include "Tester.h"

int main(int argc, char **argv) {
    boot::main(argc, argv);
//    Tester t();
    return 0;
};

