#include <iostream>
#include "Tree.h"
#include "Tree.cpp"
#include <vector>
#include <random>
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

int main() {
    std::vector<int> randomVector = getRandomVector(20);
    std::vector<std::string> stringVector = {"abcd","bbcd","cccd","dcba","liberte","egalite","fraternite"};
    Tree<std::string> tree = Tree<std::string>::createTree(stringVector);
    auto tree1 = new Tree<int>(randomVector);
    Tree<int> tree2(randomVector);

    //tree.display();
    //tree.printInOrder();
    //tree.insertAndPrint("z200000");
    //tree.printInOrder();
    //tree.display();
    //tree1.display();
    //tree1.display();
    //tree1->printInOrder();
    //tree1->display();
    //delete tree1;
    tree2.display();
    tree2.test();
    std::cout<<"/////////////////////"<<"\n";
    tree2.display();
    return 0;
}
