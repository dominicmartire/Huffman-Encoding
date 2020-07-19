#pragma once
#include <cstdint>

struct TreeNode{
    TreeNode(uint32_t weight, TreeNode* left=nullptr, TreeNode* right=nullptr);
    void insert(TreeNode*);
    bool operator<(const TreeNode&);
    
    uint32_t weight;
    TreeNode* left;
    TreeNode* right;
};

struct TreeLeaf: public TreeNode{
    TreeLeaf(char, uint32_t);

    char value;
};
