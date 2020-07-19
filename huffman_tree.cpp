#include "huffman_tree.h"
#include <iostream>

TreeNode::TreeNode(char value, uint32_t weight, std::shared_ptr<TreeNode> left, std::shared_ptr<TreeNode> right):
    value(value), weight(weight), left(left), right(right){}

TreeNode::~TreeNode(){
}

void TreeNode::insert(std::shared_ptr<TreeNode> node){
    std::shared_ptr<TreeNode> current  = this->getPtr();
    while(current->left != nullptr && current->right != nullptr){
        if(*current < *node){
            current = current->right;
       }
        else{
            current = current->left;
       }
    }
    if(*current < *node)
        current->right = node;
    else
        current->left = node;
    
}
bool TreeNode::operator<(const TreeNode& node){
    return weight < node.weight;
}

bool TreeNode::operator>(const TreeNode& node){
    return weight > node.weight;
}


    
