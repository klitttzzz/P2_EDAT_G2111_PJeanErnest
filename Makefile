CC = gcc
CFLAGS = -Wall -O2 -pedantic -ansi -g -s
LDFLAGS = -L. -lqueue -g 

# Archivos fuente y objetos
SRCS = p3_e1.c vertex.c delivery.c
OBJS = $(SRCS:.c=.o)


# Ejecutables
all: p3_e1

# Compilación de los primeros tres programas con libstack
p3_e1: p3_e1.o delivery.o vertex.o 
	$(CC) -o $@ $^ $(LDFLAGS)


# Regla general para compilar cualquier .c en un .o
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o p3_e1
