
#ifndef NEWPROJ_FILECACHEMANAGER_H
#define NEWPROJ_FILECACHEMANAGER_H

#include "CashManager.h"

using std::cout;using std::endl;

class FileCacheManager : public CashManager {
    string fileName;
public:
    FileCacheManager(const string &fileName) : fileName(fileName) {}

    void saveSolution(const string &problam, const string &solution) override {
        cout << "P:" << problam << endl << endl << endl << "S:" << solution << endl;
//todo;
    }
};

#endif //NEWPROJ_FILECACHEMANAGER_H