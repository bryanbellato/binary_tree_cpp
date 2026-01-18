#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "binary_tree.h"
#include "entity.h"
#include "graphviz_builder.h"

using namespace std;

const int NUM_ENTITIES = 11;

int main() {
    std::ifstream f("input.json");
    json data = json::parse(f);
    std::vector<int> input_numbers = data["numbers"].get<std::vector<int>>();

    std::vector<std::string> input_numbers_str;

    transform(input_numbers.begin(), input_numbers.end(), back_inserter(input_numbers_str),
              [](int i) { return std::to_string(i); });

    SearchTree searchTree;
    int nums[NUM_ENTITIES];
    string names[NUM_ENTITIES];
    Entity entities[NUM_ENTITIES];

    for(size_t i = 0; i < input_numbers.size(); ++i) {
        nums[i] = input_numbers[i];
        names[i] = input_numbers_str[i];
        Entity entity = Entity(nums[i], names[i]);
        entities[i] = entity;
        searchTree.insertEntity(entity);
    }

    cout << "==============" << endl;

    cout << "Pre: ";
    searchTree.printPreOrder();
    cout << endl;

    cout << "In: ";
    searchTree.printInOrder();
    cout << endl;

    cout << "Post: ";
    searchTree.printPostOrder();
    cout << endl;

    GraphvizBuilder viz;
    viz.generate(searchTree.getRoot(), "tree_before.dot");
    system("dot -Tpng tree_before.dot -o tree_before.png");

    searchTree.deleteEntity(entities[0].getNum());
    searchTree.deleteEntity(entities[3].getNum());
    searchTree.deleteEntity(entities[7].getNum());
    searchTree.deleteEntity(entities[5].getNum());

    cout << "==============" << endl;

    cout << "Pre: ";
    searchTree.printPreOrder();
    cout << endl;

    cout << "In: ";
    searchTree.printInOrder();
    cout << endl;

    cout << "Post: ";
    searchTree.printPostOrder();
    cout << endl;

    viz.generate(searchTree.getRoot(), "tree_after.dot");
    system("dot -Tpng tree_after.dot -o tree_after.png");

    return 0;
}
