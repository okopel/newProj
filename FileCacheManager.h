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
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;
using std::pair;
using std::ofstream;
using namespace std;

class FileCacheManager : public CashManager {
    string fileName;

    void loadSolutions() {
        ifstream loader;
        loader.open(this->fileName);
        if (!loader.is_open()) {
            return;
        }
        string buffer, p, s;
        getline(loader, buffer);
        bool isPro = true;
        bool isSol = false;
        while (buffer != "EOF") {
            if (isPro) {
                if (buffer != "\n" && !buffer.empty()) {
                    p += buffer;
                }
                if (buffer.find("end") != string::npos) {
                    isPro = false;
                    isSol = true;
                    continue;
                }
            } else if (isSol) {
                if ((!buffer.empty()) && (buffer.find("endSol") != string::npos)) {
                    isSol = false;
                    isPro = true;
                    this->saveSolution(p, s); //saving in the map
                } else if (buffer != "\n" && !buffer.empty()) {
                    s += buffer;
                }
            }
            getline(loader, buffer);
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
            saver << "\nendSol\n";
        }
        saver << "EOF\n";
        saver.close();
    }

public:
    FileCacheManager(const string &fileName) : CashManager(), fileName(fileName) {
        this->loadSolutions();
    }

    std::mutex mutex;

    void saveSolution(const string &problam, const string &solution) override {
        mutex.lock();
        this->solMap.insert(pair<string, string>(problam, solution));
        mutex.unlock();
    }

    virtual ~FileCacheManager() {
        this->backUpSolution();
    }
};

#endif //NEWPROJ_FILECACHEMANAGER_H
