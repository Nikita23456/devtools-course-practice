// Copyright 2021 Kirichenko Nikita

#include <algorithm>
#include <random>
#include "include/avl.h"

using std::max;

CNode* CAvl::Insert(const key& x, CNode* t) {
    if (t == nullptr) {
        t = new CNode;
        t->data_ = x;
        t->height_ = 0;
        t->pLeft_ = t->pRight_ = nullptr;
    } else if (x < t->data_) {
        t->pLeft_ = Insert(key(x), t->pLeft_);
        if (Height(t->pLeft_) - Height(t->pRight_) == 2) {
            if (x < t->pLeft_->data_) {
                t = SingleRightRotate(t);
            } else {
                t = DoubleRightRotate(t);
            }
        }
    } else if (x > t->data_) {
        t->pRight_ = Insert(key(x), t->pRight_);
        if (Height(t->pRight_) - Height(t->pLeft_) == 2) {
            if (x > t->pRight_->data_) {
                t = SingleLeftRotate(t);
            } else {
                t = DoubleLeftRotate(t);
            }
        }
    }

    t->height_ = max(Height(t->pLeft_), Height(t->pRight_)) + 1;
    return t;
}

CNode* CAvl::SingleRightRotate(CNode* t) {
    CNode *u = t->pLeft_;
    t->pLeft_ = u->pRight_;
    u->pRight_ = t;
    t->height_ = max(Height(t->pLeft_), Height(t->pRight_)) + 1;
    u->height_ = max(Height(u->pLeft_), t->height_) + 1;
    return u;
}

CNode* CAvl::SingleLeftRotate(CNode* t) {
    CNode *u = t->pRight_;
    t->pRight_ = u->pLeft_;
    u->pLeft_ = t;
    t->height_ = max(Height(t->pLeft_), Height(t->pRight_)) + 1;
    u->height_ = max(Height(t->pRight_), t->height_) + 1;
    return u;
}

CNode* CAvl::DoubleLeftRotate(CNode* t) {
    t->pRight_ = SingleRightRotate(t->pRight_);
    return SingleLeftRotate(t);
}

CNode* CAvl::DoubleRightRotate(CNode* t) {
    t->pLeft_ = SingleLeftRotate(t->pLeft_);
    return SingleRightRotate(t);
}

CNode* CAvl::FindMin(CNode* t) {
    if (t->pLeft_ == nullptr) {
        return t;
    } else {
        return FindMin(t->pLeft_);
    }
}

CNode* CAvl::Remove(const key& x, CNode* t) {
    CNode *temp;

    if (t == nullptr) {
        //
        // Element not found
        //
        return nullptr;
    } else if (x < t->data_) {
        //
        // Searching for element
        //
        t->pLeft_ = Remove(x, t->pLeft_);
    } else if (x > t->data_) {
        t->pRight_ = Remove(x, t->pRight_);
    } else if (t->pLeft_ && t->pRight_) {
        //
        // Element found
        // With 2 children
        //
        temp = FindMin(t->pRight_);
        t->data_ = temp->data_;
        t->pRight_ = Remove(t->data_, t->pRight_);
    } else {
        //
        // With one or zero child
        //
        temp = t;
        if (t->pLeft_ == nullptr) {
            t = t->pRight_;
        } else if (t->pRight_ == nullptr) {
            t = t->pLeft_;
        }
        delete temp;
    }
    if (t == nullptr)
        return t;

    t->height_ = max(Height(t->pLeft_), Height(t->pRight_)) + 1;

    if (Height(t->pLeft_) - Height(t->pRight_) == 2) {
        //
        // If node is unbalanced
        // If left node is deleted, right case
        //
        if (Height(t->pLeft_->pLeft_) - Height(t->pLeft_->pRight_) == 1) {
            //
            // Right right case
            //
            return SingleRightRotate(t);
        } else {
            //
            // Right left case
            //
            return DoubleRightRotate(t);
        }
    } else if (Height(t->pRight_) - Height(t->pLeft_) == 2) {
        //
        // If Right node is deleted, left case
        //
        if (Height(t->pRight_->pRight_) - Height(t->pRight_->pLeft_) == 1) {
            //
            // Left left case
            //
            return SingleLeftRotate(t);
        } else {
            //
            //
            //
            return DoubleLeftRotate(t);
        }
    }
    return t;
}

int CAvl::Height(CNode* t) {
    return (t == nullptr ? -1 : t->height_);
}

CAvl::CAvl() {
    pRoot_ = nullptr;
}

void CAvl::Insert(const key& x) {
    pRoot_ = Insert(x, pRoot_);
}

void CAvl::Remove(const key& x) {
    pRoot_ = Remove(x, pRoot_);
}

key CAvl::Find(const key & x) {
    CNode* t = this->pRoot_;
    while (t != nullptr) {
        if (x < t->data_) {
            t = t->pLeft_;
        } else if (x > t->data_) {
            t = t->pRight_;
        } else if (x == t->data_) {
            return (t->data_);
        }
    }
    return key();
}

key CAvl::GetRoot() const {
    if (pRoot_) {
        return pRoot_->data_;
    } else {
        return key();
    }
}
