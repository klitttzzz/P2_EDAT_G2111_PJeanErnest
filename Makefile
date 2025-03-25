CC = gcc
CFLAGS = -Wall -O2 -pedantic -ansi -g -s
LDFLAGS = -L. -lqueue -g 

# Archivos fuente y objetos
SRCS = p3_e1.c p3_e2b.c p3_e2a.c
OBJS = $(SRCS:.c=.o)

# Ejecutables
all: p3_e1 p3_e2a p3_e2b

# Compilación de los primeros tres programas con libstack
p2_e1a: p2_e1a.o vertex.o
	$(CC) -o $@ $^ $(LDFLAGS)

p2_e1b: p2_e1b.o vertex.o
	$(CC) -o $@ $^ $(LDFLAGS)

p2_e2: p2_e2.o vertex.o graph.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilación de los programas *_bis usando stack.c en lugar de libstack
p2_e1abis: p2_e1abis.o vertex.o stack.o
	$(CC) -o $@ $^

p2_e1bbis: p2_e1bbis.o vertex.o stack.o
	$(CC) -o $@ $^

p2_e2bis: p2_e2bis.o vertex.o graph.o stack.o
	$(CC) -o $@ $^

# Compilación de los .o

graph.o: graph.c graph.h vertex.h types.h stack.h file_utils.h
	$(CC) -c $(CFLAGS) -o $@ $<

vertex.o: vertex.c vertex.h types.h
	$(CC) -c $(CFLAGS) -o $@ $<

queue.o: queue.c queue.h types.h
	$(CC) -c $(CFLAGS) -o $@ $<

stack.o: stack.c stack.h types.h file_utils.h
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o p2_e1a p2_e1b p2_e2 p2_e1abis p2_e1bbis p2_e2bis
