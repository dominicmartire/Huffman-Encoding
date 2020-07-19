CC=cc

objects=huffman.o huffman_tree.o


huffman: $(objects)
	$(CC) -o huffman $(objects)

huffman.o: huffman.cpp
	$(CC) -c huffman.cpp -g 

huffman_tree.o: huffman_tree.cpp
	$(CC) -c huffman_tree.cpp -g

clean:
	rm $(objects)
