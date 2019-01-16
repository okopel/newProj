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


    /*  Matrix *getMatrixbackup(ifstream &inputStream) {
          auto v = new vector<vector<Point *> *>;
          int width, height;
          string buffer;
          getline(inputStream, buffer);
          width = height = stoi(buffer);
          getline(inputStream, buffer);
          Point *inition = this->getPoint(buffer);
          getline(inputStream, buffer);
          Point *goal = this->getPoint(buffer);
          for (int i = 0; i < height; i++) {

              getline(inputStream, buffer);
              v->push_back(this->getLine(i, buffer));

          }

          Matrix *matrix = new Matrix(v);
          matrix->setInition(matrix->getPointByIndex(inition->getX(), inition->getY()));
          matrix->setGoal(matrix->getPointByIndex(goal->getX(), goal->getY()));
          delete inition;
          delete goal;
          return matrix;
      }*/


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
                ans += "left";
            } else if (p->getX() > tmpPoint->getX()) {
                ans += "right";
            } else if (p->getY() < tmpPoint->getY()) {
                ans += "up";
            } else if (p->getY() > tmpPoint->getY()) {
                ans += "down";
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
            cout << "DONE!" << endl;
            delete solution;
        }
        return solutionString;
    }

    virtual void handleClient(string &pro, string &sol) {
        if (this->cashManager->isSolved(pro)) {
            sol = this->cashManager->getSolution(pro);//check if solves
        } else {
            Matrix *matrix = new Matrix(pro);//build matrix from string
            sol = this->getSolution(matrix); // solve the problem
            this->cashManager->saveSolution(pro, sol); //save the solution for later
        }
    }


};

#endif //NEWPROJ_MYMATRIXCLIENTHANDLER_H
