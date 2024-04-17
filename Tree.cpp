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
    //COUNTER
    TimeCounter timeCounter(Tree::cellInfo);
    Node* current = root;
    while(current->right != nullptr)
        current=current->right;
    return current->value;
}
template<typename T>
T Tree<T>::getMinValue() {
    //COUNTER
    TimeCounter timeCounter(Tree::cellInfo);
    Node* current = root;
    while(current->left != nullptr)
        current=current->left;
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
void Tree<T>::printPreOrder() {
    traversePreOrder(root, [](Node* node) {
        std::cout << node->value << " ";
    });
    std::cout<<std::endl;
}


template<typename T>
Tree<T>::~Tree() {
    traversePostOrder(root,[](Node * node){
        delete node;
    });
}

template<typename T>
Tree<T>::Tree(std::vector<T> vector) {
    //COUNTER
    TimeCounter timeCounter(Tree::cellInfo);
    root = Node::buildBST(vector,0,vector.size()-1);
}

template<typename T>
int Tree<T>::getHeight(Tree::Node *node) {
    if(node->left == nullptr and node->right == nullptr)
        return 1;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return leftHeight>rightHeight ? leftHeight+1 : rightHeight + 1;
}

template<typename T>
typename Tree<T>::Node *Tree<T>::Node::buildBST(std::vector<int> nums, int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end - start) / 2;
    Node *root = new Node(nums[mid]);

    root->left = buildBST(nums, start, mid - 1);
    root->right = buildBST(nums, mid + 1, end);

    return root;
}

template<typename T>
void Tree<T>::rotateLeft(Node * parent ,Node * node ) {
    if (node == nullptr or node->left == nullptr) return;
    Node * A = node;
    Node * B = node->left;
    Node * beta = B->right;

    A->left = beta;
    B->right = A;
    if(parent == nullptr){
        root = B;
        return;
    }

    if(parent->right == A)
        parent->right = B;
    else
        parent->left = B;
}
template <typename T>
void Tree<T>::rotateRight(Node * parent, Node * node) {
    if (node == nullptr or node->right == nullptr) return;
    Node * A = node;
    Node * B = node->right;
    Node * beta = B->left;

    A->right = beta;
    B->left = A;
    if(parent == nullptr){
        root = B;
        return;
    }

    if (parent->left == A)
        parent->left = B;
    else
        parent->right = B;
}

template<typename T>
void Tree<T>::updateCellInfo(TimeCounter::CellInfo cI) {
    cellInfo = cI;
}

template<typename T>
Tree<T> &Tree<T>::operator=(Tree<T> &other) {
    root = other.root;
}

template<typename T>
Tree<T>::Tree(const Tree<T> &tree) {
    root = tree.root;
}


template<typename T>
typename Tree<T>::Node * Tree<T>::removeNode(Node*  node,T key ) {
// Base case
    if (node == nullptr)
        return node;

    // Recursive calls for ancestors of
    // node to be deleted
    if (node->value > key) {
        node->left = removeNode(node->left, key);
        return node;
    }
    else if (node->value < key) {
        node->right = removeNode(node->right, key);
        return node;
    }

    // We reach here when node is the node
    // to be deleted.

    // If one of the children is empty
    if (node->left == nullptr) {
        Node* temp = node->right;
        delete node;
        return temp;
    }
    else if (node->right == nullptr) {
        Node* temp = node->left;
        delete node;
        return temp;
    }

        // If both children exist
    else {

        Node* succParent = node;

        // Find successor
        Node* succ = node->right;
        while (succ->left != nullptr) {
            succParent = succ;
            succ = succ->left;
        }

        // Delete successor.  Since successor
        // is always left child of its parent
        // we can safely make successor's right
        // right child as left of its parent.
        // If there is no succ, then assign
        // succ->right to succParent->right
        if (succParent != node)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        // Copy Successor Data to node
        node->value = succ->value;

        // Delete Successor and return node
        delete succ;
        return node;
    }
}

template<typename T>
void Tree<T>::removeNodesNTimes(T key, int n) {
    int i = 0;
    while(i++<n)
        removeNode(root,n);
}

template<typename T>
void Tree<T>::turnToRightOnlyTree() {
    Node * previous = nullptr;
    Node * current = root;
    Node * pivot;
    int i = 0;
    while(i++<15) {//TODO działa prawie dobrze tylko ten warunek nie jest prawidłowy

        if (current->left != nullptr) {
            rotateLeft(previous, current);


            previous = nullptr;
            current = root;

        } else {
            previous = current;
            current = current->right;
        }
    }

}

template<typename T>
void Tree<T>::daysAlgorithm() {
    Node *current = root;
    bool isOdd = true;
    std::vector<Node *> nodes;
    while (current->right != nullptr) {
        if (isOdd)
            nodes.push_back(current);
        current = current->right;
        isOdd = not isOdd;
    }
    rotateRight(nullptr,root);//TODO nie tak
    for (auto &&it: nodes){
        rotateRight(it, it->right);

    }

}

template<typename T>
void Tree<T>::DSWAlgorithm() {
    turnToRightOnlyTree();
    daysAlgorithm();
    daysAlgorithm();//TODO zdecydować kiedy algorytm ma być wywołany https://pl.wikipedia.org/wiki/Algorytm_DSW


}
