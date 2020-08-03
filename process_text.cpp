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
    std::vector<char> chars_to_write;
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

   std::cout << "size of tree written to file " << (int)root->serial.size() << std::endl; 

    while(!file.eof()){
       to_write = 0;
       file.get(c);
       path = encodings.at(c);
       remaining += path;
       if(remaining.size() > 8){ // see if 8 1s or 0s have been appended to remaining
           to_write = 0;
           for(int i = 0; i < 8; i++){
               to_write <<= 1;
               to_write |= (remaining[i] - '0');

           }
           
           chars_to_write.push_back(c);
           remaining = remaining.substr(8, remaining.size() - 8);
       }
    }

    out << (int)chars_to_write.size();
    for(char& c: chars_to_write){
        out << c;
    }
    std::cout << "size of encoded text " << (int)chars_to_write.size() << std::endl;
    /*deal with last remaining path in tree*/
    out << (char)remaining.size();
    int last_path = 0;

    for(int i = 0; i < 8; i++){
        last_path |= (remaining[i] - '0');
        last_path <<= 1;
    }
    out << last_path;

    out.close();
    file.close();
}


void decode_from_file(const char* file_name){
    std::ifstream file(file_name, std::ifstream::in);
    char c;
    int tree_size = 0;
    file >> tree_size;
    std::cout << "size of tree read from file " << tree_size << '\n';
    char* tree = new char[tree_size];
    file.read(tree, tree_size); // reads the vectorized huffman tree from file

    char data_size_string[sizeof(int)];
    int data_size;
    file >> data_size;
    std::cout << "size of data read from file " << data_size << '\n'; 

    char* data = new char[data_size];
    file.read(data, data_size);

    int last_char_size = 0;
    file >> last_char_size;
    
    char byte; //byte read from data
    char tree_value = '\0'; //char at the current branch in the tree;

    int data_loc = 0; //index of where we are in data read from file
    int tree_loc = 0; //index of where we are in tree

    char bit_shift = 0; //used to shift byte currently read
    char bit; //bit read from byte

    while(data_loc < data_size){
        byte = data[data_loc];
        while(tree_value == '\0'){
            bit = (byte << bit_shift) & 0x80; //get first bit of char
            if(bit == 0){
                tree_loc = (2 * tree_loc) + 1;
            }
            else{
                tree_loc = (2 * tree_loc) + 2;
            }
            tree_value = tree[tree_loc]; //get value at root after moving down tree
            bit_shift++; //increment the shift

            if(bit_shift > 7){
                bit_shift = 0;
                data_loc++;
                byte = data[data_loc];
            }
        }
        tree_value = '\0';
        tree_loc = 0;
    }

    file.close();
    delete[] data;
    delete[] tree;
}

















