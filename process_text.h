#pragma once
#include <queue>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>
#include "huffman_tree.h"

using NodePtr = std::shared_ptr<TreeNode>;

struct Comp{
    bool operator()(const NodePtr& a, const NodePtr& b){
        return *a > *b;
    }
};


void text_to_map(const char* file_name, std::map<char, uint32_t>& freqs);

void map_to_leaves(const std::map<char, uint32_t>& freqs, std::vector<NodePtr>& pointers);

void construct_tree(const std::vector<NodePtr>& pointers, NodePtr& huffman);
