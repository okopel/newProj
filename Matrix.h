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


    vector<Point *> *getLine(int lineNum, string line) {
        auto v = new vector<Point *>;
        string buffer;
        int x = 0;
        for (auto c:line) {
            if (c == ';') {
                continue;
            }
            if (c == ',') {
                if (!buffer.empty() && buffer != ",") {
                    v->push_back(new Point(x, lineNum, stoi(buffer)));
                    buffer = "";
                    x++;
                }
            } else {
                if (c == ' ') {
                    continue;
                }
                buffer += c;
            }
        }
        if (buffer != "," && !buffer.empty()) {
            v->push_back(new Point(x, lineNum, stoi(buffer)));
        }
        return v;
    }

public:

    Point *getPointByIndex(int x, int y) {
        try {
            return this->myMatrix->at(y)->at(x);
        } catch (...) {
            return nullptr;
        }
    }

    Matrix(string &pro) {
        try {
            int counter = 0;
            int xINI = -1;
            int yINI = -1;
            int xGOAL = -1;
            int yGOAL = -1;
            string buffer;
            for (auto c:pro) {
                counter++;
                if (c == ')') {
                    break;
                }
                if (c == '(') {
                    continue;
                }
                if (c == ',') {
                    if (xINI == -1) {
                        xINI = stoi(buffer);
                    } else if (yINI == -1) {
                        yINI = stoi(buffer);
                    } else if (xGOAL == -1) {
                        xGOAL = stoi(buffer);
                    }
                    buffer = "";
                } else {
                    buffer += c;
                }
            }
            yGOAL = stoi(buffer);
            pro = pro.substr(counter, pro.length() - counter + 1);
            auto v = new vector<vector<Point *> *>;
            //int width, height;
            buffer = "";
            vector<string> lines;
            for (auto c: pro) {
                if (c == ';') {
                    lines.push_back(buffer);
                    buffer = "";
                    continue;
                }
                buffer += c;
            }
            if (!buffer.empty()) {
                lines.push_back(buffer);
            }

            int lineNum = 0;
            buffer = lines.front();
            lines.erase(lines.begin());
            while (buffer != "END" && buffer != "end" && !lines.empty()) {
                if (!buffer.empty()) {
                    v->push_back(this->getLine(lineNum, buffer));
                }
                buffer = lines.front();
                lines.erase(lines.begin());
                lineNum++;
                while ((buffer.length() >= 1) && (buffer[0] == ' ')) {
                    buffer = buffer.substr(1, buffer.length() - 1);
                }
            }
            if (!buffer.empty() && (buffer != "end")) {
                v->push_back(this->getLine(lineNum, buffer));
            }
            this->myMatrix = v;
            this->setInition(this->getPointByIndex(xINI, yINI));
            this->setGoal(this->getPointByIndex(xGOAL, yGOAL));
            this->height = myMatrix->size();
            this->width = myMatrix->at(0)->size();

//            delete initionTMP;
//            delete goalTMP;

        }
        catch (...) {
            throw "Error reading the matrix";
        }

    }

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
