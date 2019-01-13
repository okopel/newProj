

#ifndef NEWPROJ_MYMATRIXCLIENTHANDLER_H
#define NEWPROJ_MYMATRIXCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Matrix.h"

class MyMatrixClient : public ClientHandler<Searchable *, vector<Point *> *> {
public:
    MyMatrixClient() {}

    MyMatrixClient(Solver<Searchable *, vector<Point *> *> *solver, CashManager *cashManager)
            : ClientHandler<Searchable *, vector<Point *> *>(solver, cashManager) {}

    void handleClient(string inputFile, string outputFile) override {

    }

};

#endif //NEWPROJ_MYMATRIXCLIENTHANDLER_H
