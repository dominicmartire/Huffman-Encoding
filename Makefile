CC=g++
FLAGS=-g


objects=huffman.o huffman_tree.o process_text.o

sources=huffman.cpp huffman_tree.cpp process_text.cpp

huffman: $(objects)
	$(CC) -o huffman $(objects) $(FLAGS)

$(objects): $(sources)
	$(CC) -c $(sources)  $(FLAGS)

clean:
	rm $(objects)
