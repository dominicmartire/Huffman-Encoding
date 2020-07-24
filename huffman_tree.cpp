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


void TreeNode::vectorize(){
    std::shared_ptr<TreeNode> current = this->getPtr();
    std::queue<std::shared_ptr<TreeNode>> node_queue;
    node_queue.push(current);
    while(!node_queue.empty()){
        current = node_queue.front();
        serial.push_back(current->value);
        node_queue.pop();
        if(current->left == nullptr){
            serial.push_back('\0');
        }
        else{
            node_queue.push(current->left);
        }
        if(current->right == nullptr){
            serial.push_back('\0');
        }
        else{
            node_queue.push(current->right);
        }
    }
}

std::ostream& operator<<(std::ostream& out, const TreeNode& root){
    for(char c: root.serial){
        out.put(c);
    }
    return out;
}










