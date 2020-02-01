#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

struct Exception {
    virtual std::string what() = 0;
};

struct Loop : public Exception {
    std::string what() { return "Loop detected in input"; }
};

struct ParallelEdge : public Exception {
    std::string what() { return "Parallel edge detected in input"; }
};

#endif
