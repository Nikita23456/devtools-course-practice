// Copyright 2021 Kirichenko Nikita

#include <gtest/gtest.h>
#include <vector>
#include "include/avl.h"

const int nLenght = 100000;

TEST(CAvlTest,
    CanCreateDefaultCAvl) {
    CAvl tree;
    ASSERT_EQ(key(), tree.GetRoot());
}

TEST(CAvlTest,
    CanInsertObject) {
    CAvl tree;
    key root = 0;
    tree.Insert(root);
    ASSERT_EQ(root, tree.GetRoot());
}

TEST(CAvlTest,
    CanFindObject) {
    CAvl tree;
    key root = 0;
    tree.Insert(root);
    ASSERT_EQ(root, tree.Find(root));
}

TEST(CAvlTest,
    CanInsertAndFindALotOfObjects) {
    CAvl tree;
    std::vector<int> vKeys = { 2, 4, 6 };

    for (int32_t i = 0; i < 2; i++) {
        tree.Insert(vKeys[i]);
    }

    for (int32_t i = 0; i < 2; i++) {
        ASSERT_EQ(vKeys[i], tree.Find(vKeys[i]));
    }
}

TEST(CAvlTest,
    CanRemoveObject) {
    CAvl tree;
    std::vector<int> vKeys = { 2, 4, 6, 9, 11, 13 };

    for (int32_t i = 0; i < 5; i++) {
        tree.Insert(vKeys[i]);
    }

    tree.Remove(vKeys[5]);
    EXPECT_EQ(key(), tree.Find(vKeys[5]));
}

TEST(CAvlTest,
    CanRemoveALotOfObjects) {
    CAvl tree;
    std::vector<int> vKeys = { 2, 4, 6, 9, 11, 13, 15, 17, 21, 23, 24 };

    for (int32_t i = 0; i < 10; i++) {
        tree.Insert(vKeys[i]);
    }

    tree.Remove(vKeys[5]);
    EXPECT_EQ(key(), tree.Find(vKeys[5]));

    tree.Remove(vKeys[1]);
    EXPECT_EQ(key(), tree.Find(vKeys[1]));

    tree.Remove(vKeys[6]);
    EXPECT_EQ(key(), tree.Find(vKeys[6]));

    tree.Remove(vKeys[2]);
    EXPECT_EQ(key(), tree.Find(vKeys[2]));

    EXPECT_EQ(vKeys[0], tree.Find(vKeys[0]));
    EXPECT_EQ(vKeys[3], tree.Find(vKeys[3]));
    EXPECT_EQ(vKeys[4], tree.Find(vKeys[4]));
    EXPECT_EQ(vKeys[7], tree.Find(vKeys[7]));
    EXPECT_EQ(vKeys[8], tree.Find(vKeys[8]));
    EXPECT_EQ(vKeys[9], tree.Find(vKeys[9]));
}

TEST(CAvlTest,
    CanRemoveAllTree) {
    CAvl tree;
    std::vector<int> vKeys = { 2, 4, 6 };

    for (int32_t i = 0; i < 2; i++) {
        tree.Insert(vKeys[i]);
    }

    for (int32_t i = 0; i < 2; i++) {
        tree.Remove(vKeys[i]);
    }

    EXPECT_EQ(key(), tree.GetRoot());
}

TEST(CAvlTest,
    CanInsertObjectsAscending) {
    CAvl tree;

    for (int32_t i = 0; i < nLenght; i++) {
        tree.Insert(i);
        EXPECT_EQ(i, tree.Find(i));
    }
}

TEST(CAvlTest,
    CanInsertObjectsDescending) {
    CAvl tree;

    for (int32_t i = nLenght; i != 0; i--) {
        tree.Insert(i);
        EXPECT_EQ(i, tree.Find(i));
    }
}

TEST(CAvlTest,
    CanInsertObjectWithDLRotate) {
    CAvl tree;

    tree.Insert(4);
    tree.Insert(5);
    tree.Insert(7);
    tree.Insert(9);
    tree.Insert(8);
    EXPECT_EQ(8, tree.Find(8));
}

TEST(CAvlTest,
    CanInsertObjectWithDRRotate) {
    CAvl tree;

    tree.Insert(5);
    tree.Insert(6);
    tree.Insert(3);
    tree.Insert(1);
    tree.Insert(2);
    EXPECT_EQ(2, tree.Find(2));
}

TEST(CAvlTest,
    CanRemoveObjectsAscending) {
    CAvl tree;

    for (int32_t i = 0; i != nLenght; i++) {
        tree.Insert(i);
    }

    for (int32_t i = 0; i != nLenght; i++) {
        tree.Remove(i);
        EXPECT_EQ(key(), tree.Find(i));
    }
}

TEST(CAvlTest,
    CanRemoveObjectsDescending) {
    CAvl tree;

    for (int32_t i = 0; i != nLenght; i++) {
        tree.Insert(i);
    }

    for (int32_t i = nLenght; i != 0; i--) {
        tree.Remove(i);
        EXPECT_EQ(key(), tree.Find(i));
    }
}

TEST(CAvlTest,
    CanRemoveRoot) {
    CAvl tree;

    for (int32_t i = 0; i != nLenght; i++) {
        tree.Insert(i);
    }

    key nRoot = tree.GetRoot();
    tree.Remove(nRoot);
    EXPECT_EQ(key(), tree.Find(nRoot));
}

TEST(CAvlTest,
    CanRemoveNonexistRootChild) {
    CAvl tree;
    tree.Insert(0);
    tree.Remove(0);
    EXPECT_EQ(0, tree.Find(0));
    EXPECT_EQ(key(), tree.Find(-1));
}

TEST(CAvlTest,
    CanRemoveNonexistObject) {
    CAvl tree;

    for (int32_t i = 0; i != nLenght; i++) {
        tree.Insert(i);
    }

    key nRoot = tree.GetRoot();
    tree.Remove(-1);
    for (int32_t i = 0; i != nLenght; i++) {
        EXPECT_EQ(i, tree.Find(i));
    }
    EXPECT_EQ(key(), tree.Find(-1));
}
