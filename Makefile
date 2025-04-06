CC = gcc
CFLAGS = -Wall -O2 -pedantic -ansi -g -s
LDFLAGS = -L. -lqueue -g 

# Archivos fuente y objetos

SRCS = p3_e1.c p3_e2b.c p3_e2a.c p3_e3.c
OBJS = $(SRCS:.c=.o)

# Ejecutables
all: p3_e1 p3_e2a p3_e2b p3_e3

# Compilación de los primeros tres programas con libqueue
p3_e1: p3_e1.o graph.o vertex.o stack.o delivery.o
	$(CC) -o $@ $^ $(LDFLAGS)

p3_e2a: p3_e2a.o graph.o queue.o vertex.o stack.o delivery.o
	$(CC) -o $@ $^ $(CFLAGS)

p3_e2b: p3_e2b.o graph.o vertex.o stack.o queue.o
	$(CC) -o $@ $^ $(CFLAGS)

p3_e3: p3_e3.o list.o
	$(CC) -o $@ $^ $(CFLAGS)

# Compilación de los .o

graph.o: graph.c graph.h vertex.h types.h stack.h file_utils.h stack.h queue.h
	$(CC) -c $(CFLAGS) -o $@ $<

vertex.o: vertex.c vertex.h types.h
	$(CC) -c $(CFLAGS) -o $@ $<

delivery.o: delivery.c delivery.h types.h queue.h vertex.h
	$(CC) -c $(CFLAGS) -o $@ $<

stack.o: stack.c stack.h types.h file_utils.h
	$(CC) -c $(CFLAGS) -o $@ $<

queue.o: queue.c queue.h types.h file_utils.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Limpieza de archivos intermedios
clean:
	rm -f *.o p3_e1 p3_e2a p3_e2b p3_e3
