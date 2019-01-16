
#ifndef NEWPROJ_TESTER_H
#define NEWPROJ_TESTER_H

#include "FileCacheManager.h"


#include "MyMatrixClientHandler.h"
#include "MyParallelServer.h"
//using namespace server_side;
#include "Server.h"

using std::string;

class Tester {

public:
    Tester() {
        auto *cm = new FileCacheManager("db.txt");
        auto *solver = new SolveSearchAdapter(new Bestfs());
        ClientHandler<Searchable *, vector<Point *> *> *clientHandler = new MyMatrixClient(solver, cm);
        auto *server = new MyParallelServer<Searchable *, vector<Point *> *>();
        server->open(5800, clientHandler);
    }
};


#endif //NEWPROJ_TESTER_H
