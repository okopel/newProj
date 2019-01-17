/*****************************
 * Project part B of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * Januar 2019
 ******************************/

#ifndef NEWPROJ_MYMATRIXCLIENTHANDLER_H
#define NEWPROJ_MYMATRIXCLIENTHANDLER_H

#include <fstream>
#include <algorithm>
#include "ClientHandler.h"
#include "Matrix.h"

using std::cout;
using std::ifstream;
using std::ofstream;
using std::stoi;

class MyMatrixClient : public ClientHandler<Searchable *, vector<Point *> *> {

    Point *getPoint(string line) {
        int delimiter = line.find(",");
        return new Point(stoi(line.substr(0, delimiter)), stoi(line.substr(delimiter + 1, line.size())), 0);
    }

    string printPath(vector<Point *> *path) {
        string ans;
        auto tmpPoint = path->front();
        path->erase(path->begin());
        //cout << tmpPoint->printIndex();
        for (auto p: *path) {
            if (!ans.empty()) {
                ans += "->";
            }
            if (p->getX() < tmpPoint->getX()) {
                ans += "Left";
            } else if (p->getX() > tmpPoint->getX()) {
                ans += "Right";
            } else if (p->getY() < tmpPoint->getY()) {
                ans += "Up";
            } else if (p->getY() > tmpPoint->getY()) {
                ans += "Down";
            }
            //cout << p->printIndex();
            tmpPoint = p;
            path->pop_back();
        }
        return ans;
    }

public:

    MyMatrixClient(Solver<Searchable *, vector<Point *> *> *solver, CashManager *cashManager) :
            ClientHandler<Searchable *, vector<Point *> *>(solver, cashManager) {}


    string getSolution(Matrix *matrix) {
        auto solution = this->solver->solve(matrix);
        string solutionString;
        if (solution == nullptr) {
            solutionString = "There is no path";
        } else {
            reverse(solution->begin(), solution->end());
            solutionString = this->printPath(solution);
            // cout << "DONE!" << endl;
            delete solution;
        }
        return solutionString;
    }

    virtual void handleClient(string &pro, string &sol) {
        if (this->cashManager->isSolved(pro)) {
            sol = this->cashManager->getSolution(pro);//check if solves
        } else {
            string proToSave = pro;
            Matrix *matrix = new Matrix(pro);//build matrix from string
            sol = this->getSolution(matrix); // solve the problem
            this->cashManager->saveSolution(proToSave, sol); //save the solution for later
        }
    }


};

#endif //NEWPROJ_MYMATRIXCLIENTHANDLER_H
