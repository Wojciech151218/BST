#include <iostream>
#include "Tree.h"
#include "Tree.cpp"
#include <vector>
#include <random>
#include "library.h"



std::vector<int> getRandomVector(int size){
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the size of the vector
    const int vectorSize = size;

    // Create a vector to store random integers
    std::vector<int> randomVector;

    // Generate and fill the vector with random integers
    std::uniform_int_distribution<int> dis(1, 100); // Range of random integers [1, 100]
    for (int i = 0; i < vectorSize; ++i) {
        randomVector.push_back(dis(gen)); // Generates a random integer and adds it to the vector
    }
    return randomVector;
}
std::vector<int> getSortedArray(int size){
    std::vector<int> result;
    for (int i = 0; i < size; ++i) {
        result.push_back(i);
    }
    return result;
}

int main() {
    auto tree = Tree<int>::createTreeFromRandom(getRandomVector(10));
    printf("%d\n",tree.getMaxValue());
    printf("%d\n",tree.getMinValue());
    tree.printInOrder();
    tree.printPreOrder();
    //tree.removeNodesNTimes(3,3);

    tree.display();
    printf("////////////////////\n");



    tree.DSWAlgorithm();
    tree.display();

    //delete tree;//usuwanie metoda postorder


    return 0;
    std::vector<std::vector<int>> vectors;
    std::vector<int> sizes ;
    for(int i=1;i<=20;i++)
        sizes.push_back(i*250);

    for(auto &&it :sizes){
        vectors.push_back(getSortedArray(it));
    }



    TimeCounter::generateDirectory("/home/wojciech/CLionProjects/algi2");
    int size = 0;
    TimeCounter::addFileName("Budowanie_drzewa");
    std::string bstDegenerated = "zdegenerowane_drzewo";
    TimeCounter::addColumnName(bstDegenerated);

    std::vector<Tree<int>*>  trees;

    for(auto&&it : vectors){
        TimeCounter::addIndex(sizes[size]);
        Tree<int>::updateCellInfo({sizes[size++],bstDegenerated});
        trees.push_back(new Tree<int>(it));
    }
    size = 0;
    TimeCounter::generateFile();
    TimeCounter::addFileName("maksymalna_wartość");
    for(auto&&it : trees){
        Tree<int>::updateCellInfo({sizes[size++],bstDegenerated});
        it->getMaxValue();
    }
    size = 0;
    TimeCounter::generateFile();
    TimeCounter::generateExcelSheet("/home/wojciech/CLionProjects/algi2/generateExcel.py");
    return 0;
}
