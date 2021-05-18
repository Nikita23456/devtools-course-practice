// Copyright 2021 Zaitsev Andrey

#include <vector>
#include <stack>
#include <stdexcept>

#include "../include/rb_trees.h"

Node::Node(int _value, bool _color, Node *_left, Node *_right,
    Node *_parent) : value(_value), color(_color), left(_left),
    right(_right), parent(_parent) {}

Node::Node(const Node& node) : value(node.value), color(node.color),
left(node.left), right(node.right), parent(node.parent) {}

Node& Node::operator=(const Node& node) {
    if (this == &node)
        return *this;
    value = node.value;
    color = node.color;
    left = node.left;
    right = node.right;
    parent = node.parent;

    return *this;
}

bool Node::operator==(const Node& node) {
    if (value == node.value && color == node.color)
        return true;

    return false;
}

bool Node::operator!=(const Node& node) {
    return !(*this == node);
}

RBTree::RBTree() {
    NIL = new Node();
    _root = NIL;
    current = NIL;
    nodes_number = 0;
    counter = 0;
}

RBTree::RBTree(Node *node) {
    NIL = new Node();
    _root = node;
    current = NIL;
    nodes_number = 1;
    counter = 0;

    _root->left = NIL;
    _root->right = NIL;
    _root->parent = NIL;
}

RBTree::RBTree(const std::vector<int>& vec) {
    NIL = new Node();
    _root = NIL;
    current = NIL;
    nodes_number = 0;
    counter = 0;

    for (int i : vec) {
        Node *node = new Node(i);
        nodes_ptr.emplace_back(node);
        insertNode(node);
    }
}

RBTree::~RBTree() {
    delete NIL;
    for (size_t i = 0; i < nodes_ptr.size(); i++)
        delete nodes_ptr[i];
}

unsigned int RBTree::getNodesNumber() const {
    return nodes_number;
}

Node* RBTree::findNode(const int& value) {
    Node* current = _root;

    while (current != NIL) {
        if (value == current->value)
            return current;
        else if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }

    return NIL;
}

void RBTree::insertNode(Node *node) {
    if (findNode(node->value))
        throw "Node with this value is already in the tree";

    Node *par = NIL;
    Node *node_place = _root;

    while (node_place != NIL) {
        par = node_place;
        if (node->value < node_place->value)
            node_place = node_place->left;
        else
            node_place = node_place->right;
    }

    node->parent = par;

    if (par == NIL)
        _root = node;
    else if (node->value < par->value)
        par->left = node;
    else
        par->right = node;

    node->left = NIL;
    node->right = NIL;
    node->color = RED;

    shuffle_for_insert(node);

    nodes_number++;
}

void RBTree::removeNode(const int value) {
    Node* find_node = findNode(value);
    if (find_node == nullptr)
        throw std::invalid_argument("No that data in tree");

    Node *node = find_node;
    Node *par = current;
    Node *node_place;

    bool y_original_color = par->color;

    if (node->left == NIL) {
        node_place = node->right;
        transplant(node, node->right);
    } else if (node->right == NIL) {
        node_place = node->left;
        transplant(node, node->left);
    } else {
        par = get_minimum(node->right);
        y_original_color = par->color;
        node_place = par->right;

        if (par->parent == node) {
            node_place->parent = par;
        } else {
            transplant(par, par->right);
            par->right = node->right;
            par->right->parent = par;
        }

        transplant(node, par);
        par->left = node->left;
        par->left->parent = par;
        par->color = node->color;
    }
    delete[] node;
    if (y_original_color == BLACK)
        shuffle_for_remove(node_place);
}

void RBTree::removingNodes(const std::vector<int>& vec, int i) {
    if (getNodesNumber() != 0) {
        removeNode(vec[i]);
        i++;
        removingNodes(vec, i);
    }
}

void RBTree::shuffle_for_insert(Node *node) {
    while (node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node *uncle = node->parent->parent->right;

            if (uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    left_rotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                right_rotate(node->parent->parent);
            }
        } else {
            Node *uncle = node->parent->parent->left;

            if (uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    right_rotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                left_rotate(node->parent->parent);
            }
        }
    }

    _root->color = BLACK;
}

void RBTree::left_rotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        _root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RBTree::right_rotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;

    if (y->right != NIL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        _root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void RBTree::transplant(Node *x, Node *y) {
    if (x->parent == NIL)
        _root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->parent = x->parent;
}

void RBTree::shuffle_for_remove(Node *node) {
    while (node != _root && node->color == BLACK) {
        if (node == node->parent->left) {
            Node *tmp = node->parent->right;

            if (tmp->color == RED) {
                tmp->color = BLACK;
                node->parent->color = RED;
                left_rotate(node->parent);
                tmp = node->parent->right;
            }

            if (tmp->left->color == BLACK && tmp->right->color == BLACK) {
                tmp->color = RED;
                node = node->parent;
            } else {
                if (tmp->right->color == BLACK) {
                    tmp->left->color = BLACK;
                    tmp->color = RED;
                    right_rotate(tmp);
                    tmp = node->parent->right;
                }
                tmp->color = node->parent->color;
                node->parent->color = BLACK;
                tmp->right->color = BLACK;
                left_rotate(node->parent);
                node = _root;
            }
        } else {
            Node *tmp = node->parent->left;

            if (tmp->color == RED) {
                tmp->color = BLACK;
                node->parent->color = RED;
                right_rotate(node->parent);
                tmp = node->parent->left;
            }

            if (tmp->right->color == BLACK && tmp->left->color == BLACK) {
                tmp->color = RED;
                node = node->parent;
            } else {
                if (tmp->left->color == BLACK) {
                    tmp->right->color = BLACK;
                    tmp->color = RED;
                    left_rotate(tmp);
                    tmp = node->parent->left;
                }
                tmp->color = node->parent->color;
                node->parent->color = BLACK;
                tmp->left->color = BLACK;
                right_rotate(node->parent);
                node = _root;
            }
        }
    }

    node->color = BLACK;
}

Node* RBTree::get_minimum(Node * const node) {
    current = node;

    while (current->left != NIL)
        current = current->left;

    return current;
}

Node* RBTree::getRoot() const {
    return _root;
}
