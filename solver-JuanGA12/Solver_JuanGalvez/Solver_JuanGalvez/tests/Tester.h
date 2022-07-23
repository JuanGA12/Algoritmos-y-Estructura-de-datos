//
// Created by Juan Galvez on 2020-05-24.
//

#ifndef SOLVER_JUANGA12_TESTER_H
#define SOLVER_JUANGA12_TESTER_H

#include <stdexcept>
#include <iostream>
#include <assert.h>
#include <string.h>
#include "../Solver.h"

using namespace std;

#ifndef NDEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif

class Tester {
public:
    static void execute();
};


#endif //SOLVER_JUANGA12_TESTER_H
