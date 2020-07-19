#include "process_text.h"

void text_to_map(const char* file_name, std::map<char, uint32_t>& freqs){ //get frequency of each character in text
    std::ifstream file(file_name, std::ifstream::in);
    char c;
    while(!file.eof()){
        file.get(c);
        if(freqs[c]){
            freqs[c]++;
        }
        else{
            freqs[c]=1;
        }
    }
}

void map_to_leaves(const std::map<char, uint32_t>& freqs, std::vector<NodePtr>& pointers){
    for(auto& p: freqs){
        pointers.push_back(std::make_shared<TreeNode>(p.first, p.second));
    }
}

void construct_tree(const std::vector<NodePtr>& pointers, NodePtr& huffman){
    std::priority_queue<NodePtr, std::vector<NodePtr>, Comp> pq;
    for(auto& ptr: pointers){
        pq.push(ptr);
    }
    while(pq.size() > 1){
        NodePtr first = pq.top();
        pq.pop();
        NodePtr second = pq.top();
        pq.pop();
        NodePtr new_node = std::make_shared<TreeNode>('\0', first->weight + second->weight, first, second);
        pq.push(new_node);
    }
}






