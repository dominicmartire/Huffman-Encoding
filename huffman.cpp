#include <iostream>
#include "huffman_tree.h"

int main(int argc, char* argv[]){
    TreeNode insert(7);
    TreeNode tree(5);
    TreeNode insert2(3);
    tree.insert(&insert);
    tree.insert(&insert2);

    TreeNode insert3(8);
    tree.insert(&insert3);

    std::cout << (tree.left)->weight << std::endl;
    std::cout<< (tree.right)->weight << std::endl;
    std::cout << (insert.right)->weight << " " << (tree.right)->right->weight << std::endl;

    TreeLeaf leaf('c', 3);
    std::cout << leaf.value << " " << leaf.weight << std::endl;
    insert3.insert(&leaf);
    std::cout << (insert3.left)->weight << std::endl;
}
