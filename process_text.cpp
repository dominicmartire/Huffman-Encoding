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
    int size = 0;
    while(pq.size() > 1){
        NodePtr first = pq.top();
        pq.pop();
        NodePtr second = pq.top();
        pq.pop();
        NodePtr new_node = std::make_shared<TreeNode>('\0', first->weight + second->weight, first, second);
        pq.push(new_node);
        size++;
    }
    huffman = pq.top();
}

void encodings_helper(const NodePtr& huffman, std::map<char,std::string>& encodings, std::string path){
    if(huffman->value != '\0'){
        encodings[huffman->value] = path;
    }
        else{
        encodings_helper(huffman->left, encodings, std::string(path + "0"));
        encodings_helper(huffman->right, encodings, std::string(path+"1"));
    }
}


void char_encodings(const NodePtr& huffman, std::map<char,std::string>& encodings){
    encodings_helper(huffman, encodings, std::string(""));
}


char decode(const std::string& path, const NodePtr& huffman){
    NodePtr current = huffman;
    for(char c: path){
        if(c == '0'){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }
    return current->value;
}

void encode_to_file(const std::map<char,std::string>& encodings, const char* in_file, const char* out_file, NodePtr& root){
    
    std::ifstream file(in_file, std::ifstream::in);
    std::ofstream out(out_file, std::ofstream::binary);
    char to_write, c;

    std::string remaining = "";
    std::string path; // string that each character is mapped to


    //add tree data to file
    if(root->serial.size() == 0){
        root->vectorize();
    }
    out << (int)root->serial.size(); //write size of tree to file
    const NodePtr& write_tree = root;

    out << *write_tree;


    char max_path_len = 0;
    for(auto& p: encodings){
        if(p.second.size() > max_path_len){
            max_path_len = p.second.size();
        }
    }

    out.put(max_path_len + 1); // get maximum depth of tree in order to deal with last byte written to file

    while(!file.eof()){
       to_write = 0;
       file.get(c);
       path = encodings.at(c);
       remaining += path;
       if(remaining.size() > 8){ // see if 8 1s or 0s have been appended to remaining
           to_write = 0;
           for(int i = 0; i < 8; i++){
               to_write |= (remaining[i] - '0');

               to_write <<= 1;
           }
           
           out.put(to_write);
           remaining = remaining.substr(8, remaining.size() - 8);
       }
    }
    //handle last character if remaining is less than 8 bits
    /* 
    might cause an issue if remaining isn't 8 characters long
    for example the last character is mapped to 1100
    the last byte written to the file will be 00001100
    and that path might not exist in the tree, or it will
    lead to an incorrect character
    */
    to_write = 0;
    for(int i = 0; i < max_path_len + 1; i++){ //pad with max_path_len + 1 null bytes in order to know when to stop reading
        out.put(to_write);
    }

    char size_of_last = 0;
    if(remaining.size() > 0){
        for(int i = 0; i < remaining.size(); i++){
            to_write |= (remaining[i] - '0');
            to_write <<= 1;

            size_of_last++;
        }
    }
    out.put(size_of_last); // will be between 0 and 8. when decoding, if this byte equals 4 and the following byte is 00000101 then the last path read will be 0101
    out.put(to_write);

}


void decode_from_file(const char* file_name){
    std::ifstream file(file_name, std::ifstream::in);
    char c;
    int size = 0;
    file >> size;
    char* tree = new char[size];
    file.read(tree, size);
    std::cout << tree << std::endl;

    delete tree;
}

















