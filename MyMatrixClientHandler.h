

#ifndef NEWPROJ_MYMATRIXCLIENTHANDLER_H
#define NEWPROJ_MYMATRIXCLIENTHANDLER_H

#include <fstream>
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
        auto v = new vector<vector<Point *> *>;
        int width, height;
        string buffer;
        getline(inputStream, buffer);
        width = height = stoi(buffer);
        getline(inputStream, buffer);
//        inputStream >> buffer;
        Point *inition = this->getPoint(buffer);
//        inputStream >> buffer;
        getline(inputStream, buffer);
        Point *goal = this->getPoint(buffer);
        for (int i = 0; i < height; i++) {

            getline(inputStream, buffer);
            v->push_back(this->getLine(i, buffer));

        }
        Matrix *matrix = new Matrix(v);
        matrix->setInition(inition);
        matrix->setGoal(goal);
        return matrix;
    }

public:

    MyMatrixClient(Solver<Searchable *, vector<Point *> *> *solver, CashManager *cashManager) :
            ClientHandler<Searchable *, vector<Point *> *>(solver, cashManager) {}

    void handleClient(string inputFile, string outputFile) override {
        auto matrixes = new vector<Matrix *>;
        ifstream inputStream;
        inputStream.
                open(inputFile);
        if (!inputStream.

                is_open()

                ) {
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
        for (auto vec: *matrixes) {
            auto solution = this->solver->solve(vec);
            for (auto point: *solution) {
                cout << point->printIndex() << "\t";
            }
            cout << endl;
        }
        inputStream.close();
        outputStream.close();
    }

};

#endif //NEWPROJ_MYMATRIXCLIENTHANDLER_H
