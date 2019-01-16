

#ifndef NEWPROJ_STRINGREVERSEHANDLER_H
#define NEWPROJ_STRINGREVERSEHANDLER_H

#include <string>
#include "Solver.h"

using std::string;
using std::swap;

class StringReverserHandler : public Solver<string, string> {

    string solve(string p) {
        string s = p;
        int n = s.length();
        for (int i = 0; i < n / 2; i++)
            swap(s[i], s[n - i - 1]);
        return s;
    }


};

#endif //NEWPROJ_STRINGREVERSEHANDLER_H
