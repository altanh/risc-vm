CC=g++
CFLAGS=-Wall -g -std=c++11

DEPS = lexer.h parser.h token.h
OBJ = lexer.o parser.o token.o vasm.o

%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

vasm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o

