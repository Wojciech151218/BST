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

template <typename T>
class Tree {

public:
    struct Node{
        Node * left;
        Node * right;
        Node * up;
        T value;
        explicit Node(T value):value(value),left(nullptr),right(nullptr),up(nullptr){};
        ~Node(){
                delete left;
                delete right;
        }
    };
    T getMaxValue();
    static Tree<T> createTree(std::vector<T>);
    void printInOrder();
    void display(Node *currentRoot = nullptr,int depth =0,std::string colour = "");
    explicit Tree(Node *root) : root(root) {};
    void insertAndPrint(T);
    void emptyTree();
    ~Tree();
    Tree(std::vector<T>);
    void test(){
        rotateLeft(root);
    }

private:
    Node * root;
    void traverseInOrder(Node * node, void (*function)(Node*));
    void traversePreOrder(Node * node, void (*function)(Node*));
    void traversePostOrder(Node * node, void (*function)(Node*));
    Node * insert(Node * root ,T value,void (*function)(Node *,Node *) = [](Node * a ,Node * b){});
    Node * insert(Node * root ,Node * node,void (*function)(Node *,Node *) = [](Node * a ,Node * b){});
    void rotateLeft(Node * node);
    void rotateRight(Node * node);


};


#endif ALGI2_TREE_H