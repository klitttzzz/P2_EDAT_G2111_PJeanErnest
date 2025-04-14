#include <stdio.h>
#include <string.h>

#include "graph.h"

int main(int argc, char const *argv[]){
    /*int i;*/
    char *endptr1, *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    FILE *f = fopen("city_graph.txt", "r");
    Graph *g= graph_init();
    Vertex** vertices=graph_get_vertex(g);
    if (!f) {
        fprintf(stderr, "Error: Could not open file g2.txt\n");
        return 1;
    }
     
    if (!g) {
        fprintf(stderr, "Error: Could not initialize graph\n");
        fclose(f);
        return 1;
    }
    
    if (!vertices) {
        fprintf(stderr, "Error: Could not retrieve vertices\n");
        graph_free(g);
        fclose(f);
        return 1;
    }
    fprintf(stdout,"\nInput: \n");
    if(!graph_readFromFile(f,g)){
        fprintf(stderr, "\nError");
    }
    graph_print(stdout,g);
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <start_vertex> <end_vertex>\n", argv[0]);
        graph_free(g);
        fclose(f);
        return 1;
    }
    
    

    if (*endptr1 != '\0' || *endptr2 != '\0') {
        printf("Error en la conversión de números");
        return 1;
    }
    fprintf(stdout,"From vertex: %ld ", val1);
    fprintf(stdout,"\nTo vertex: %ld ", val2);
    fprintf(stdout,"\nOutput:\n");
    if(!graph_breathSearch(g, val1,val2)){
        printf("Error en graph_breathSearch");
        return 1;
    }
   
    
    graph_free(g);
    
    return 0;
}