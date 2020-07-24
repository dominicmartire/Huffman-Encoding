#pragma once
#include <queue>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

void char_encodings(const NodePtr& huffman, std::map<char,std::string>& encodings);

char decode(const std::string& path, const NodePtr& huffman);

void encode_to_file(const std::map<char,std::string>& encodings, const char* in_file, const char* out_file, NodePtr& root);

void decode_from_file(const char* file_name);
