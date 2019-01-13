
#ifndef NEWPROJ_FILECACHEMANAGER_H
#define NEWPROJ_FILECACHEMANAGER_H

#include "CashManager.h"

class FileCacheManager : public CashManager {
    string inputFileName;
    string outputFileName;
public:
    FileCacheManager(const string &inputFileName, const string &outputFileName) : inputFileName(inputFileName),
                                                                                  outputFileName(outputFileName) {}

    void saveSolution(const string &problam, const string &solution) override {
//todo;
    }
};

#endif //NEWPROJ_FILECACHEMANAGER_H
