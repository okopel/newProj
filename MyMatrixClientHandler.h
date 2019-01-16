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
    vector<Point *> *getLine(int lineNum, string line) {
        auto v = new vector<Point *>;
        string buffer;
        int x = 0;
        for (auto c:line) {
            if (c == ',') {
                v->push_back(new Point(x, lineNum, stoi(buffer)));
                buffer = "";
                x++;
            } else {
                if (c == ' ') {
                    continue;
                }
                buffer += c;
            }
        }
        v->push_back(new Point(x, lineNum, stoi(buffer)));
        return v;
    }

    Point *getPoint(string line) {
        int delimiter = line.find(",");
        return new Point(stoi(line.substr(0, delimiter)), stoi(line.substr(delimiter + 1, line.size())), 0);
    }

    Matrix *getMatrix(ifstream &inputStream) {
        try {
            auto v = new vector<vector<Point *> *>;
            //int width, height;
            string buffer;
            int lineNum = 0;
            getline(inputStream, buffer);
            while (buffer != "END" && buffer != "end") {
                v->push_back(this->getLine(lineNum, buffer));
                getline(inputStream, buffer);
                lineNum++;
                while ((buffer.length() >= 1) && (buffer[0] == ' ')) {
                    buffer = buffer.substr(1, buffer.length() - 1);
                }
            }
            auto begin = v->at(v->size() - 2);
            auto goal = v->at(v->size() - 1);
            v->erase(v->begin() + v->size() - 1);//delete goal
            v->erase(v->begin() + v->size() - 1);//delete goal
            // v->erase(v->begin() + v->size() - 1);//delete inition
            //v->erase(v->end() - 1);//delete begin
            Point *inition = new Point(begin->at(0)->getCost(), begin->at(1)->getCost(), -1);
            Point *goalPoint = new Point(goal->at(0)->getCost(), goal->at(1)->getCost(), -1);

            Matrix *matrix = new Matrix(v);
            matrix->setInition(matrix->getPointByIndex(inition->getX(), inition->getY()));
            matrix->setGoal(matrix->getPointByIndex(goalPoint->getX(), goalPoint->getY()));

            delete inition;
            delete goalPoint;
            return matrix;
        }
        catch (...) {
            throw "Error reading the matrix";
        }
    }

    Matrix *getMatrixbackup(ifstream &inputStream) {
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

    void myFunc(string inputFile, string outputFile) {
        auto matrixes = new vector<Matrix *>;
        ifstream inputStream;
        inputStream.open(inputFile);
        if (!inputStream.is_open()) {
            throw "Error in input file";
        }
        ofstream outputStream;
        outputStream.open(outputFile);
        if (!outputStream.is_open()) {
            throw "Error in output file";
        }
        string buffer;
        getline(inputStream, buffer);
        int numOfGraphs = stoi(buffer);
        for (int i = 0; i < numOfGraphs; i++) {
            matrixes->push_back(this->getMatrix(inputStream)
            );
        }
        int i = 0;
        for (auto vec: *matrixes) {
            //cout << "Here is a solution:" << i++ << endl;
            auto solution = this->solver->solve(vec);
            string solutionString;
            if (solution == nullptr) {
                solutionString = "There is no path";
            } else {
                reverse(solution->begin(), solution->end());
                solutionString = this->printPath(solution);
                delete solution;
            }
            //    cout << solutionString;
            //   cout << endl << "End Of Solution." << endl;
            this->cashManager->saveSolution(vec->getStringToCache(), solutionString);
        }
        cout << "DONE!" << endl;
        for (auto mat: *matrixes) {
            delete mat;
        }
        delete matrixes;
        delete this->solver;
        inputStream.close();
        outputStream.close();
    }

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

    void handleClient(string inputFile, string outputFile) override {
        ifstream inputStream;
        inputStream.open(inputFile);
        if (!inputStream.is_open()) {
            throw "Error in input file";
        }
        ofstream outputStream;
        outputStream.open(outputFile);
        if (!outputStream.is_open()) {
            throw "Error in output file";
        }
        string buffer;
        Matrix *m = this->getMatrix(inputStream);
        string problam = m->getStringToCache();
        string solution;
        if (this->cashManager->isSolved(problam)) {
            solution = this->cashManager->getSolution(problam);
        } else {
            solution = this->getSolution(m);
            this->cashManager->saveSolution(problam, solution);
        }
        cout << solution << endl;
        delete m;
        delete this->solver;
        inputStream.close();
        outputStream.close();
    }

};

#endif //NEWPROJ_MYMATRIXCLIENTHANDLER_H
