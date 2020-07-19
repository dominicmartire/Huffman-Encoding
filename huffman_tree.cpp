#include "huffman_tree.h"
#include <iostream>
TreeNode::TreeNode(uint32_t weight, TreeNode* left, TreeNode* right):
    weight(weight), left(left), right(right){}

void TreeNode::insert(TreeNode* node){
    TreeNode* current  = this;
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


TreeLeaf::TreeLeaf(char val, uint32_t weight):value(val), TreeNode(weight){}
    
