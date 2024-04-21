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
    traverseInOrder(node->left,function);//trawersujemy lewe pod-drzewo
    function(node);// wywołujemy funkcję
    traverseInOrder(node->right,function);//trawersujemy prawe pod-drzewo
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
        current=current->right;//trawersujemy do liścia najbardziej po prawo tam znajduję się największy element
    return current->value;
}
template<typename T>
T Tree<T>::getMinValue() {
    //COUNTER
    TimeCounter timeCounter(Tree::cellInfo);
    Node* current = root;
    while(current->left != nullptr)
        current=current->left;//trawersujemy do liścia najbardziej po lewo tam znajduję się najmniejszy element
    return current->value;
}

template<typename T>
Tree<T> Tree<T>::createTreeFromRandom(std::vector<T> vector) {
    auto result = Tree<T>(new Node(vector.back()));
    vector.pop_back();
    for(auto&&it:vector)
        result.insert(result.root,it);
    return  result;
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
void Tree<T>::rotateLeft(Node*& tmp,Node*& grand) {
    Node* oldTmp = tmp;
    tmp = tmp->right;
    grand->right = tmp;
    oldTmp->right = tmp->left;
    tmp->left = oldTmp;
    if(oldTmp == root) root = tmp;
}
template<typename T>
void Tree<T>::rotateRight(Node*& tmp,Node*& grand) {

    if (not tmp or not tmp->left) return;
    Node* oldTmp = tmp;
    tmp = tmp->left;
    oldTmp->left = tmp->right;
    tmp->right = oldTmp;
    grand->right = tmp;
    if(oldTmp == root) root = tmp;//rightRotate
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
typename Tree<T>::Node* Tree<T>::removeNode(Node* node, T key) {
    // Przypadek podstawowy: jeśli węzeł jest pusty, zwracamy go.
    if (node == nullptr)
        return node;

    // Jeśli wartość węzła jest większa niż klucz, rekursywnie
    // przechodzimy lewe poddrzewo w poszukiwaniu węzła do usunięcia.
    if (node->value > key) {
        node->left = removeNode(node->left, key);
        return node;
    }
        // Jeśli wartość węzła jest mniejsza niż klucz, rekursywnie
        // przechodzimy prawe poddrzewo w poszukiwaniu węzła do usunięcia.
    else if (node->value < key) {
        node->right = removeNode(node->right, key);
        return node;
    }

    // Dotarliśmy tutaj, gdy węzeł jest węzłem do usunięcia.

    // Jeśli jedno z dzieci węzła jest puste, usuwamy węzeł
    // i zwracamy jego niepuste dziecko.
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

    else {
        // W przypadku, gdy usuwany węzeł ma obu potomków, musimy znaleźć
// następnika w drzewie, który jest węzłem o najmniejszej wartości
// większej niż wartość usuwanego węzła. Następnie zamieniamy
// wartość usuwanego węzła na wartość następnika, aby zachować
// własności drzewa BST. Następnie usuwamy następnika, ponieważ
// jego wartość została przeniesiona do miejsca usuwanego węzła.
        Node* succParent = node;
        Node* succ = node->right;
        while (succ->left != nullptr) {
            succParent = succ;
            succ = succ->left;
        }
// Po znalezieniu następnika, musimy zastąpić go w drzewie. Jeśli
// rodzic następnika nie jest usuwanym węzłem, to ustawiamy lewe
// dziecko rodzica na prawe dziecko następnika. W przeciwnym razie,
// ustawiamy prawe dziecko rodzica na prawe dziecko następnika.
        if (succParent != node)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

// Zamieniamy wartość usuwanego węzła na wartość następnika.
        node->value = succ->value;

// Usuwamy następnika, ponieważ jego wartość została przeniesiona
// do miejsca usuwanego węzła.
        delete succ;

// Zwracamy usuwany węzeł (który teraz ma wartość następnika),
// aby zachować strukturę drzewa BST.
        return node;
    }
}

template<typename T>
void Tree<T>::removeNodesNTimes(T key, int n) {
    int i = 0;
    while(i++<n)//wywołujemy removeNode n razy
        removeNode(root,key);
}

 // Metoda BSTToVine przekształca drzewo BST (Binary Search Tree)
// w formę płaskiego drzewa poprzez rotacje w prawo. Zwraca liczbę
// węzłów przekształconych w procesie.
template<typename T>
int Tree<T>::BSTToVine(Node* grand) {
    int count = 0;

    // Tworzymy wskaźnik tmp do przeglądania
    // i prawego spłaszczenia danego drzewa BST.
    Node* tmp = grand->right;

    // Przechodzimy, dopóki tmp nie stanie się NULLem
    while (tmp) {

        // Jeśli lewy węzeł istnieje dla węzła
        // wskazywanego przez tmp, to wykonujemy
        // rotację w prawo.
        if (tmp->left) {
            rotateRight(tmp, grand);
        }

            // Jeśli lewy węzeł nie istnieje
            // dodajemy 1 do count i
            // kontynuujemy dalsze przeglądanie w prawo,
            // aby spłaszczyć pozostałe drzewo BST.
        else {
            count++;
            grand = tmp;
            tmp = tmp->right;
        }
    }

    return count;
}

// Metoda compress kompresuje drzewo BST
// przez wykonywanie m rotacji w lewo, zaczynając od węzła grand.
template<typename T>
void Tree<T>::compress(Node* grand, int m) {
    // Tworzymy wskaźnik tmp do przeglądania
    // i kompresowania danego drzewa BST.
    Node* tmp = grand->right;

    // Przechodzimy i wykonujemy m razy rotację w lewo,
    // aby skompresować podane drzewo BST w postaci wstążki.
    for (int i = 0; i < m; i++) {
        rotateLeft(tmp, grand);
        grand = tmp;//trawersujemy w prawo
        tmp = tmp->right;// tmp to następny prawy węzeł
    }
}


// Metoda DSWAlgorithm implementuje algorytm DSW (Day-Stout-Warren),
// który przekształca drzewo BST w zrównoważone drzewo.
template<typename T>
void Tree<T>::DSWAlgorithm() {
    // Tworzymy węzeł pomocniczy
    Node* grand = new Node(T(0));

    // Przypisujemy prawe poddrzewo węzła dummy jako korzeń wejściowy drzewa
    grand->right = root;

    // Pobieramy liczbę węzłów w wejściowym drzewie BST i
    // przekształcamy je w prawą winorośl
    // faza 1 algorytmu Daya 46 strona wykładu
    int count = BSTToVine(grand);

    // wysokość drzewa, w którym wszystkie poziomy
    // są w pełni wypełnione.
    int h = log2(count + 1);

    // liczba węzłów do przedostatniego poziomu.
    int m = pow(2, h) - 1;

    // Rotacja w lewo dla nadmiarowych węzłów na ostatnim poziomie
    // faza 2 algorytmu Daya strona 48 wykładu:
    compress(grand, count - m);


    // Rotacja w lewo, aż m stanie się równe 0.
    // Krok jest wykonywany zgodnie z algorytmem, aby
    // zrównoważyć drzewo BST.
    for (m = m / 2; m > 0; m /= 2)
        compress(grand, m);
}
