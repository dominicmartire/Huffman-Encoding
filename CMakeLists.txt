cmake_minimum_required(VERSION "3.7.1")

project("huffman")
file(GLOB huffman_src
    "*.h"
    "*.cpp")

add_executable(huffman ${huffman_src}) 
