#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include <queue>
#include <iostream>

struct TreeNode: public std::enable_shared_from_this<TreeNode>{
    TreeNode(char value = '\0', uint32_t weight=0, std::shared_ptr<TreeNode> left=nullptr, std::shared_ptr<TreeNode> right=nullptr);
    ~TreeNode();
    void insert(std::shared_ptr<TreeNode>);
    bool operator<(const TreeNode&);
    bool operator>(const TreeNode&);
    friend std::ostream& operator<<(std::ostream& out, const TreeNode&);

    std::shared_ptr<TreeNode> getPtr(){
        return shared_from_this();
    }

    void vectorize();

    char value;
    uint32_t weight;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    std::vector<char> serial;
};


