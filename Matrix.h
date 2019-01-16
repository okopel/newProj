/*****************************
 * Project part B of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * Januar 2019
 ******************************/

#ifndef NEWPROJ_MATRIX_H
#define NEWPROJ_MATRIX_H

#include "Searchable.h"
#include <vector>

using std::vector;
using std::cout;
using std::endl;

class Matrix : public Searchable {
    vector<vector<Point *> *> *myMatrix;
    int height;
    int width;
public:

    Point *getPointByIndex(int x, int y) {
        try {
            return this->myMatrix->at(x)->at(y);
        } catch (...) {
            return nullptr;
        }
    }

    Matrix() {}

    Matrix(vector<vector<Point *> *> *myMatrix) : Searchable(), myMatrix(myMatrix) {
        this->height = myMatrix->size();
        this->width = myMatrix->at(0)->size();
    }

    string getStringToCache() {
        string answer;
        answer += "(" + to_string(this->inition->getX()) + "," + to_string(this->inition->getY());
        answer += "," + to_string(this->goal->getX()) + "," + to_string(this->goal->getY()) + ")";
        for (auto item:*this->myMatrix) {
            for (auto node:*item) {
                answer += to_string(node->getCost()) + ",";
            }
            answer += ";";
        }

        return answer;
    }

    void print() {
        for (auto line:*this->myMatrix) {
            for (auto *col:*line) {
                cout << (col)->print() << "\t";
            }
            cout << endl;
        }

    }

    vector<Point *> *getAllPossibleStates(Searchable *searchble, Point *myPlace) override {
        auto posStates = new vector<Point *>;

        int x = myPlace->getX();
        int y = myPlace->getY();
        if (x < 0 || y < 0 || x > this->width || y > this->height) {
            return nullptr;
        }
        if (x < this->width) {//rohav
            posStates->push_back(this->getPointByIndex(x + 1, y));
        } else {
            posStates->push_back(nullptr);
        }
        if (x > 0) {
            posStates->push_back(this->getPointByIndex(x - 1, y));
        } else {
            posStates->push_back(nullptr);
        }
        if (y < this->height) {
            posStates->push_back(this->getPointByIndex(x, y + 1));
        } else {
            posStates->push_back(nullptr);
        }
        if (y > 0) {
            posStates->push_back(this->getPointByIndex(x, y - 1));
        } else {
            posStates->push_back(nullptr);
        }
        return posStates;
    }

    virtual ~Matrix() {
        for (auto m:*this->myMatrix) {
            for (auto n:*m) {
                delete n;
            }
            delete m;
        }
        delete this->myMatrix;
    }
};


#endif //NEWPROJ_MATRIX_H
