
#ifndef NEWPROJ_MYPARALLELSERVER_H
#define NEWPROJ_MYPARALLELSERVER_H

#include "Server.h"
#include <thread>
#include <netinet/in.h>
#include <vector>
#include <strings.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <queue>
#include <list>

using namespace server_side;
using std::thread;
using std::queue;
using std::list;
using std::ref;
using std::cout;
using std::endl;

template<class P, class S>
class MyParallelServer : public server_side::Server<P, S> {

    static void parallel(ClientHandler<string, string> *clientHandler, int new_sock, bool *isRun) {
        cout << "start" << endl;
        string nextBuffer, connectedBuffer;
        char buffer[4096];
        string strBuff;

        *isRun = true;

        try {
            while (/*!parallelStop*/true) {
                cout << connectedBuffer << endl;
                bzero(buffer, 256);
                read(new_sock, buffer, 255);
                connectedBuffer += buffer;
                if (connectedBuffer[connectedBuffer.size() - 1] != '\n') {
                    connectedBuffer += "\n";
                }
                string strBuff(connectedBuffer);
                if (strBuff.find("end") != string::npos) {
                    string answer;
                    if (connectedBuffer[0] == '\n') {
                        connectedBuffer[0] = ' ';
                    }
                    clientHandler->handleClient(connectedBuffer, answer);
                    const char *cstr = answer.c_str();
                    write(new_sock, cstr, answer.size());
                    break;
                }
            }
        } catch (...) {
        }
        close(new_sock);
        *isRun = false;
        cout << "stop" << endl;

    }

    static void startPar(int port, ClientHandler<string, string> *clientHandler, bool *parallelStop) {
        int s = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in serv;
        serv.sin_addr.s_addr = INADDR_ANY;
        serv.sin_port = htons(port);
        serv.sin_family = AF_INET;
        queue<thread *> threads;
        list<bool *> isRunning;
        bool isFirst = true;

        bind(s, (sockaddr *) &serv, sizeof(serv));
        listen(s, 20000);
        struct sockaddr_in client;
        socklen_t clilen = sizeof(client);

        timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        while (!parallelStop) {
            try {
                int new_sock;
                setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
                new_sock = accept(s, (struct sockaddr *) &client, &clilen);

                bool isTimeOut = !isFirst;
                for (auto &r : isRunning) {
                    if (*r) {
                        isTimeOut = false;
                        break;
                    }
                }
                if (isTimeOut) {
                    if (new_sock < 0) {
                        if (errno == EWOULDBLOCK) {
                            cout << "timeout!" << endl;
                            break;
                        } else {
                            perror("other error");
                            break;
                        }
                    }
                }

                if (new_sock >= 0) {
                    bool *isRun = new bool;
                    isRunning.push_back(isRun);
                    threads.push(new thread(parallel, clientHandler, new_sock, isRun));
                    isFirst = false;
                }
            } catch (...) {
                cout << "connection with client stopped" << endl;
            }
        }
        while (!threads.empty()) {
            threads.front()->join();
            delete threads.front();
            threads.pop();
        }
        for (auto &i : isRunning) {
            delete i;
        }


    }

public:
    MyParallelServer() {
        this->shouldStop = false;
    }

    int open(int port, ClientHandler<P, S> *clientHandler) override {
        //  thread *t = new thread(this->startPar, port, clientHandler, ref(this->shouldStop));
        // t->join();
        //delete t;
    }


    void stop() override {
        this->shouldStop = true;
    }

};

#endif //NEWPROJ_MYPARALLELSERVER_H
