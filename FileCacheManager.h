
#ifndef NEWPROJ_FILECACHEMANAGER_H
#define NEWPROJ_FILECACHEMANAGER_H

#include "CashManager.h"

class FileCacheManager : public CashManager {
    string fileName;
public:
    FileCacheManager(const string &fileName) : fileName(fileName) {}

    void saveSolution(const string &problam, const string &solution) override {
//todo;
    }
};

#endif //NEWPROJ_FILECACHEMANAGER_H
