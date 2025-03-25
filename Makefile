CC = gcc
CFLAGS = -Wall -O2 -pedantic -ansi -g -s
LDFLAGS = -L. -lstack -g 

# Archivos fuente y objetos
SRCS = p2_e1a.c p2_e1b.c vertex.c
OBJS = $(SRCS:.c=.o)

SRCS_BIS = p2_e1abis.c p2_e1bbis.c p2_e2bis.c stack.c
OBJS_BIS = $(SRCS_BIS:.c=.o)

# Ejecutables
all: p2_e1a p2_e1b p2_e2 p2_e1abis p2_e1bbis p2_e2bis

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

# Regla general para compilar cualquier .c en un .o
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o p2_e1a p2_e1b p2_e2 p2_e1abis p2_e1bbis p2_e2bis
