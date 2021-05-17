// Copyright 2021 Kirichenko Nikita

#ifndef MODULES_RB_TREES_INCLUDE_RB_OPERATION_H_
#define MODULES_RB_TREES_INCLUDE_RB_OPERATION_H_

#include <string>
#include <vector>
#include "include/rb_trees.h"

class RBOperation {
 public:
    explicit RBOperation(const int _argc) : argc(_argc) {}
    virtual ~RBOperation() = default;
    static RBOperation* makeOperation(std::string op);
    virtual std::string operator()(RBTree* tree,
        const std::vector<int>& arg) = 0;
    int getArgc() { return argc; }
 protected:
    int isNIL(Node* node);
 private:
    int argc;
};

class InsertOperation : public RBOperation {
 public:
    InsertOperation() : RBOperation(2) {}
    std::string operator()(RBTree* tree, const std::vector<int>& arg) override;
};

class FindOperation : public RBOperation {
 public:
    FindOperation() : RBOperation(2) {}
    std::string operator()(RBTree* tree, const std::vector<int>& arg) override;
};

class RemoveOperation : public RBOperation {
 public:
    RemoveOperation() : RBOperation(2) {}
    std::string operator()(RBTree* tree, const std::vector<int>& arg) override;
};

class GetRootOperation : public RBOperation {
 public:
    GetRootOperation() : RBOperation(1) {}
    std::string operator()(RBTree* tree, const std::vector<int>& arg) override;
};

#endif  // MODULES_RB_TREES_INCLUDE_RB_OPERATION_H_
