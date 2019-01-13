
#ifndef NEWPROJ_MATRIX_H
#define NEWPROJ_MATRIX_H

#include "Searchable.h"
#include <vector>

using std::vector;

class Matrix : public Searchable {
    vector<vector<Point *> *> *myMatrix;
    int height;
    int width;
public:
    Matrix() {}

    Matrix(vector<vector<Point *> *> *myMatrix) : myMatrix(myMatrix) {
        this->height = myMatrix->size();
        this->width = myMatrix->at(0)->size();
    }

    vector<Point *> *getAllPossibleStates(Point *myPlace) override {
        return Searchable::getAllPossibleStates(myPlace);//todo
    }

};


#endif //NEWPROJ_MATRIX_H
