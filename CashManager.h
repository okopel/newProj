/*****************************
 * Project part B of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * Januar 2019
 ******************************/
#ifndef NEWPROJ_CASHMANAGER_H
#define NEWPROJ_CASHMANAGER_H

#include <string>
#include <map>

using std::string;
using std::map;

class CashManager {
protected:
    map<string, string> solMap;
public:
    bool isSolved(const string &problam);

    string getSolution(const string &problam);

    virtual void saveSolution(const string &problam, const string &solution) = 0;

};

#endif //NEWPROJ_CASHMANAGER_H
