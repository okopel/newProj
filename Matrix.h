
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

    Point *getPointByIndex(int x, int y) {
        try {
            return this->myMatrix->at(y)->at(x);
        } catch (...) {
            return nullptr;
        }
    }

public:
    Matrix() {}

    Matrix(vector<vector<Point *> *> *myMatrix) : myMatrix(myMatrix) {
        this->height = myMatrix->size();
        this->width = myMatrix->at(0)->size();
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

};


#endif //NEWPROJ_MATRIX_H
