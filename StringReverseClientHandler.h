

#ifndef NEWPROJ_STRINGREVERSECLIENTHANDLER_H
#define NEWPROJ_STRINGREVERSECLIENTHANDLER_H

#include <iostream>
#include "ClientHandler.h"

using std::cout;
using std::endl;

class StringReverseClientHandler : public ClientHandler<string, string> {

public:
    StringReverseClientHandler(Solver<string, string> *solver, CashManager *cashManager) : ClientHandler(solver,
                                                                                                         cashManager) {}

    void handleClient(string &pro, string &sol) override {
        sol = this->solver->solve(pro);
        cout << sol << endl;
    }

};

#endif //NEWPROJ_STRINGREVERSECLIENTHANDLER_H
