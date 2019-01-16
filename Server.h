
#ifndef NEWPROJ_SERVER_H
#define NEWPROJ_SERVER_H


#include "ClientHandler.h"
#include <string>
#include <stdio.h>

using std::string;

#define TIME_OUT 2

namespace server_side {

    template<class Problem, class Solution>
    class Server {
    protected:
        int socketId;
        bool shouldStop;

    public:
        virtual int open(int port, ClientHandler<Problem, Solution> *clientHandler) = 0;

        virtual void stop() = 0;

        //todo func to get info
    };
}

#endif //NEWPROJ_SERVER_H
