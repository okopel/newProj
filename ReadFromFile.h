
#ifndef NEWPROJ_READFROMFILE_H
#define NEWPROJ_READFROMFILE_H

#include <string>
#include <fstream>
#include "Matrix.h"

using std::string;
using std::ifstream;

class ReadFromFile {
    Matrix *myMatrix;
    string fileName;

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
            auto initionVec = v->at(v->size() - 2);
            auto goalVec = v->at(v->size() - 1);

            Point *initionTMP = new Point(initionVec->at(0)->getCost(), initionVec->at(1)->getCost(), -1);
            Point *goalTMP = new Point(goalVec->at(0)->getCost(), goalVec->at(1)->getCost(), -1);

            v->erase(v->begin() + v->size() - 2, v->begin() + v->size());//delete goal and inition vec

            Matrix *matrix = new Matrix(v);
            matrix->setInition(matrix->getPointByIndex(initionTMP->getX(), initionTMP->getY()));
            matrix->setGoal(matrix->getPointByIndex(goalTMP->getX(), goalTMP->getY()));

            delete initionTMP;
            delete goalTMP;
            return matrix;
        }
        catch (...) {
            throw "Error reading the matrix";
        }
    }

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

public:
    ReadFromFile(const string &inputFile) : fileName(inputFile) {
        ifstream inputStream;
        inputStream.open(inputFile);
        if (!inputStream.is_open()) {
            throw "Error in input file";
        }
        this->myMatrix = this->getMatrix(inputStream);

        inputStream.close();
    }

    string getStringOfMatrix() {
        return this->myMatrix->getStringToCache();
    }
};

#endif //NEWPROJ_READFROMFILE_H
