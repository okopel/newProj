

#ifndef NEWPROJ_MYMATRIXCLIENTHANDLER_H
#define NEWPROJ_MYMATRIXCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Matrix.h"

using std::cout;

class MyMatrixClient : public ClientHandler<Searchable *, vector<Point *> *> {
public:

    MyMatrixClient(Solver<Searchable *, vector<Point *> *> *solver, CashManager *cashManager)
            : ClientHandler<Searchable *, vector<Point *> *>(solver, cashManager) {}

    void handleClient(string inputFile, string outputFile) override {
        auto v = new vector<vector<Point *> *>;
        for (int i = 0; i < 5; i++) {
            auto line = new vector<Point *>;
            for (int j = 0; j < 5; j++) {
                line->push_back(new Point(i, j, 123 - (i * j) + i * j - i % 2));
            }
            v->push_back(line);
        }
        Matrix *m = new Matrix(v);
        m->print();
    }

};

#endif //NEWPROJ_MYMATRIXCLIENTHANDLER_H
