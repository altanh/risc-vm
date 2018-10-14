CC=gcc
CFLAGS=-Wall -g -std=c11

DEPS = cpu.h mem.h inst.h util.h
OBJ = cpu.o mem.o inst.o risc-vm.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

risc-vm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

tests: tests.c risc-vm
	$(CC) -o $@ tests.c $(CFLAGS)	

.PHONY: clean

clean:
	rm -f *.o

