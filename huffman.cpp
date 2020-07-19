#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include "huffman_tree.h"
#include "process_text.h"


int main(int argc, char* argv[]){
    std::map<char, uint32_t> m;
    text_to_map(argv[1], m);
    std::vector<NodePtr> pointers;
    map_to_leaves(m, pointers); 
   
    NodePtr root = std::make_shared<TreeNode>();
    construct_tree(pointers, root);
    return 0;
} 
