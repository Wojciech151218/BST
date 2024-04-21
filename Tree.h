//
// Created by wojciech on 25.03.24.
//

#ifndef ALGI2_TREE_H
#define ALGI2_TREE_H
//#include "Node.h"

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <chrono>
#include <utility>
#include "library.h"
#include <cmath>


template <typename T>
class Tree {

public:
    struct Node{
        Node * left;
        Node * right;
        T value;
        Node(T value):value(value),left(nullptr),right(nullptr){};
        static Node* buildBST(std::vector<int> nums, int start, int end);
        virtual ~Node(){};
    };
    T getMaxValue();
    T getMinValue();
    static Tree<T> createTreeFromRandom(std::vector<T>);
    void printInOrder();
    void printPreOrder();
    void display(Node *currentRoot = nullptr,int depth =0,std::string colour = "");
    explicit Tree(Node *root) : root(root) {};
    static void updateCellInfo(TimeCounter::CellInfo);
    Tree& operator=(Tree& other);
    Tree(const Tree& other);
    ~Tree();
    Tree(std::vector<T>);
    void removeNodesNTimes(T key ,int n);
    void DSWAlgorithm();
    void test();


protected:
    Node * root;
    static inline TimeCounter::CellInfo cellInfo;
    int getHeight(Node * node);
    void traverseInOrder(Node * node, void (*function)(Node*));
    void traversePreOrder(Node * node, void (*function)(Node*));
    void traversePostOrder(Node * node, void (*function)(Node*));
    Node * insert(Node * root ,T value,void (*function)(Node *,Node *) = [](Node * a ,Node * b){});
    Node * insert(Node * root ,Node * node,void (*function)(Node *,Node *) = [](Node * a ,Node * b){});
    void rotateLeft(Node *& ,Node *&);
    void rotateRight(Node *& ,Node *&);
    Node* removeNode(Node* ,T);
    void compress(Node* grand, int m);
    int  BSTToVine(Node* );




};


#endif ALGI2_TREE_H