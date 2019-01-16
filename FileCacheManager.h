/*****************************
 * Project part B of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * Januar 2019
 ******************************/
#ifndef NEWPROJ_FILECACHEMANAGER_H
#define NEWPROJ_FILECACHEMANAGER_H

#include "CashManager.h"
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::pair;
using std::ofstream;

class FileCacheManager : public CashManager {
    string fileName;

    void loadSolutions() {
        ifstream loader;
        loader.open(this->fileName);
        if (!loader.is_open()) {
            return;
        }
        string p, s;
        getline(loader, p);
        getline(loader, s);
        while (p != "EOF" && !p.empty() && !loader.eof()) {
            this->saveSolution(p, s);
            getline(loader, p);
            getline(loader, s);
        }

    }

    void backUpSolution() {
        ofstream saver(this->fileName);

        if (!saver.is_open()) {
            throw "Error in open file of saving";
        }
        for (auto prob: this->solMap) {
            saver << prob.first;
            saver << prob.second;
        }
        saver << "\nEOF";
    }

public:
    FileCacheManager(const string &fileName) : CashManager(), fileName(fileName) {
        this->loadSolutions();
    }

    void saveSolution(const string &problam, const string &solution) override {
        this->solMap.insert(pair<string, string>(problam, solution));
    }

    virtual ~FileCacheManager() {
        this->backUpSolution();
    }
};

#endif //NEWPROJ_FILECACHEMANAGER_H
