#ifndef GRAPHVIZ_BUILDER_H
#define GRAPHVIZ_BUILDER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "binary_tree.h"

class GraphvizBuilder {
private:
    std::ofstream file;
    std::map<int, std::vector<std::string>> level_nodes;
    const std::string colors[6] = {"blue", "red", "darkgreen", "purple", "chocolate", "teal"};

    // convert pointer to hex string
    std::string getAddr(void* ptr) {
        if (!ptr) {
          return "NULL";
        }
        std::stringstream ss;
        ss << "0x" << std::hex << (uintptr_t)ptr;
        return ss.str();
    }

    // get ID for the respective pointer
    std::string getID(void* ptr) {
        std::stringstream ss;
        ss << "node_" << (uintptr_t)ptr;
        return ss.str();
    }

    void drawCluster(NodeType* node, int level) {
        if (!node) return;

        std::string id = getID(node);
        std::string color = colors[level % 6];
        std::string addr = getAddr(node);

        level_nodes[level].push_back(id);

        file << "    subgraph cluster_" << (uintptr_t)node << " {\n";
        file << "        label = \"Stack Frame: " << addr << "\";\n";
        file << "        fontsize=12; color=" << color << "; fontcolor=" << color << ";\n";

        // head node
        file << "        " << id << " [label=\"{ <data> Val: " << node->entity.getNum()
             << " | { <left> " << getAddr(node->left)
             << " | <right> " << getAddr(node->right) << " } }\"];\n";

        // left node
        std::string l_stub = id + "_L";
        std::string l_val = (node->left) ? std::to_string(node->left->entity.getNum()) : "nil";
        file << "        " << l_stub << " [label=\"{ <data> " << l_val << " | { nil | nil } }\"];\n";

        // right node
        std::string r_stub = id + "_R";
        std::string r_val = (node->right) ? std::to_string(node->right->entity.getNum()) : "nil";
        file << "        " << r_stub << " [label=\"{ <data> " << r_val << " | { nil | nil } }\"];\n";

        // connect head to the nodes
        file << "        " << id << ":left -> " << l_stub << ";\n";
        file << "        " << id << ":right -> " << r_stub << ";\n";

        file << "    }\n";

        if (node->left) {
            drawCluster(node->left, level + 1);
            file << "    " << l_stub << ":data -> " << getID(node->left) << " [color=" << color << "];\n";
        }

        if (node->right) {
            drawCluster(node->right, level + 1);
            file << "    " << r_stub << ":data -> " << getID(node->right) << " [color=" << color << "];\n";
        }
    }

public:
    void generate(NodeType* root, std::string filename) {
        file.open(filename);

        file << "digraph G {\n";
        file << "    graph [rankdir=TB, nodesep=0.5, ranksep=1.0, newrank=true];\n";
        file << "    node [shape=record, fontname=\"Courier New\", fontsize=10];\n";
        file << "    edge [arrowhead=vee, arrowsize=0.8];\n\n";

        if (root) {
            std::string rootAddr = getAddr(root);
            file << "    start [shape=Mdiamond, label=\"Root (" << root->entity.getNum() << ")\\n" << rootAddr << "\"];\n";
            file << "    start -> " << getID(root) << ";\n";

            drawCluster(root, 0);
        }

        file << "\n    // Alignment\n";
        for (auto const& [level, ids] : level_nodes) {
            file << "    { rank=same; ";
            for (const auto& id : ids) file << id << "; ";
            file << "}\n";
        }

        file << "}\n";
        file.close();
        std::cout << "Graphviz file generated: " << filename << std::endl;
    }
};

#endif
