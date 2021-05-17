// Copyright 2021 Kirichenko Nikita

#ifndef MODULES_RB_TREES_INCLUDE_RB_TREES_APP_H_
#define MODULES_RB_TREES_INCLUDE_RB_TREES_APP_H_

#include <string>
#include <sstream>
#include "include/rb_trees.h"

class RBTreeApp {
 public:
    RBTreeApp() = default;
    std::string operator()(int argc, const char** argv);
 private:
    std::string help(const char* appname, const char* message = "");
    bool validateNumberOfArguments(int argc, const char** argv);
    int parseToValue(std::string strval);
    RBTree _rb;
    std::stringstream _sstream;
};

#endif  // MODULES_RB_TREES_INCLUDE_RB_TREES_APP_H_
