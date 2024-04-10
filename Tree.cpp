//
// Created by wojciech on 25.03.24.
//

#include "Tree.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
template <typename T>
void Tree<T>::traverseInOrder( Node * node, void (*function)(Node*)){
    if (node == nullptr)
        return;
    traverseInOrder(node->left,function);
    function(node);
    traverseInOrder(node->right,function);
}
template <typename T>
void Tree<T>::traversePreOrder( Node * node, void (*function)(Node*)){
    if (node == nullptr)
        return;
    function(node);
    traversePreOrder(node->left,function);
    traversePreOrder(node->right,function);
}
template <typename T>
void Tree<T>::traversePostOrder( Node * node, void (*function)(Node*)){
    if (node == nullptr)
        return;
    traversePostOrder(node->left,function);
    traversePostOrder(node->right,function);
    function(node);
}
template <typename T>
typename Tree<T>::Node * Tree<T>::insert(Node * root ,T value,void (*function)(Node*,Node*)){
    if(root == nullptr)
        return new Node(value);
    if(value < root->value){
        function(root,root->left);
        root->left = insert(root->left,value,function);
    } else{
        function(root,root->right);
        root->right = insert(root->right,value,function);
    }
    return root;
}
template<typename T>
typename Tree<T>::Node * Tree<T>::insert(Node * root ,Node * node,void (*function)(Node*,Node*)){
    if (root == nullptr) {
        return node;
    }
    if(node->value < root->value){
        function(root,root->left);
        root->left = insert(root->left,node,function);
    } else{
        function(root,root->right);
        root->right = insert(root->right,node,function);
    }
    return root;

}
template<typename T>
T Tree<T>::getMaxValue() {
        Node* current = root;
        while(current->right != nullptr)
            current=current->right;
        return current->value;
}

template<typename T>
Tree<T> Tree<T>::createTree(std::vector<T> vector) {
    return Tree<T>(vector);
}



template<typename T>
void Tree<T>::display(Node * currentRoot ,int depth,std::string colour ){
    if(not depth)  currentRoot = root;
    if (currentRoot == nullptr) return;

    // Display right subtree
    display(currentRoot->right, depth + 1,GREEN);

    // Print current node
    for (int i = 0; i < depth; ++i) {
        std::cout << "   "; // Adjust indentation based on depth
    }
    std::cout <<colour<< "|--" << currentRoot->value << RESET<<std::endl;

    // Display left subtree
    display(currentRoot->left, depth + 1,YELLOW);
}

template<typename T>
void Tree<T>::printInOrder() {

    traverseInOrder(root, [](Node* node) {
        std::cout << node->value << " ";
    });
    std::cout<<std::endl;

}

template<typename T>
void Tree<T>::insertAndPrint(T value) {
    insert(root,value,[](Node * a , Node * b){
        std::cout << ((a != nullptr) ? a->value : "finnish") <<" "<<
        ((b != nullptr) ? b->value : "finnish") << "\n";

    });
}


template<typename T>
Tree<T>::~Tree() {
    delete root;
}

template<typename T>
Tree<T>::Tree(std::vector<T> vector) {
    Node * node = new Node(vector.front());
    root = node;
    vector.erase(vector.begin());
    for (const auto value : vector) {
        insert(root,value);
    }
}

template<typename T>
void Tree<T>::rotateLeft(Tree::Node *node) {
    Node * temp = node->right;
    node->right = temp->left;
    temp->left = node ;

}

