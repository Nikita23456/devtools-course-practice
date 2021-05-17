// Copyright 2021 Kirichenko Nikita

#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include "include/rb_trees_app.h"
#include "include/rb_operation.h"

std::string RBTreeApp::operator()(int argc, const char** argv) {
    if (!validateNumberOfArguments(argc, argv)) {
        return _sstream.str();
    }
    try {
        for (int i = 1; i < argc;) {
            RBOperation* op = RBOperation::makeOperation(*(argv + i));
            std::vector<int> args;
            for (int j = 1; j < op->getArgc(); ++j)
                args.push_back(parseToValue(*(argv + i + 1)));
            _sstream << op->operator()(&_rb, args);
            i += op->getArgc();
            delete op;
        }
        return _sstream.str();
    }
    catch(const std::exception& exc) {
        return exc.what();
    }
}

std::string RBTreeApp::help(const char* appname, const char* message) {
    return std::string(message) + "This is a Red-black tree application.\n\n" +
        "Please provide arguments in the following format:\n\n" +
        "  $ " + appname + " <actions> \n\n" +
        "Where <actions> are: \n\n" +
        "getRoot - get root element from tree\n" +
        "find <data> - find element by data\n" +
        "insert <node> - insert node into tree\n" +
        "remove <data> - remove element from tree\n ";
}

bool RBTreeApp::validateNumberOfArguments(int argc, const char** argv) {
    if (argc == 1) {
        _sstream << help(argv[0]);
        return false;
    }
    return true;
}

int RBTreeApp::parseToValue(std::string strval) {
    for (size_t i = 1; i < strval.size(); ++i) {
        if (!std::isdigit(strval[i]))
            throw
            std::invalid_argument("Invalid value: " + std::string(strval));
    }
    try {
        auto value = std::stoi(strval);
        return value;
    }
    catch(...) {
        throw std::invalid_argument("Invalid value: " + strval);
    }
}
