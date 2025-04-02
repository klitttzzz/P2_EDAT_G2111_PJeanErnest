/**
 * @file graph.c
 * @author Ernest Çelo
 * @date Created on February 07, 2021
 * @version 1.0
 * @brief Library to manage the Graph ADT
 *
 * @see
 */

#include <string.h>
#include "graph.h"
#include "stack.h"
#include "queue.h"
#define MAX_VTX 4096

/* START [Private_functions] */
long *graph_getWhiteConnectionsFromId(const Graph *g, long id);
int graph_getNumberOfWhiteConnectionsFromId(const Graph *g, long id);
int _graph_findVertexByTag(const Graph *g, char *tag);
Vertex *_graph_findVertexById(const Graph *g, long id);
Status _graph_insertEdgeFromIndices(Graph *g, const long origIx, const long destIx);
int _graph_getNumConnections(const Graph *g, int ix);
long *_graph_getConnections(const Graph *g, int ix);
void _graph_setVertexState(Graph *g, Label l);
/* END [Private_functions] */

struct _Graph
{
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};

int get_vertex_from_id(const Graph *g, long id);

Graph *graph_init()
{
    int i, j;
    Graph *graph = NULL;

    if (!(graph = (Graph *)calloc(1, sizeof(Graph))))
    {
        return NULL;
    }

    for (i = 0; i < graph->num_vertices; i++)
    {
        for (j = 0; j < graph->num_vertices; j++)
        {
            graph->connections[i][j] = FALSE;
        }
    }

    graph->num_vertices = 0;
    graph->num_edges = 0;

    return graph;
}

void graph_free(Graph *g)
{
    int i;
    for (i = 0; i < g->num_vertices; i++)
    {
        free(g->vertices[i]);
    }

    free(g);
}

Status graph_newVertex(Graph *g, char *desc)
{
    Vertex *vertex = vertex_initFromString(desc);
    int i;

    if (!g || !desc)
    {
        return ERROR;
    }
    vertex->index = g->num_vertices;
    for (i = 0; i < g->num_vertices; i++)
    {
        if (vertex_getId(vertex) == vertex_getId(g->vertices[i]))
        {
            return OK;
        }
    }
    g->vertices[g->num_vertices] = vertex;
    vertex->index = g->num_vertices;
    g->num_vertices++;

    /*vertex_print(stdout,vertex);*/
    return OK;
}

Status graph_newEdge(Graph *g, long orig, long dest)
{

    if (g == NULL || orig < 0 || dest < 0)
    {
        return ERROR;
    }

    g->connections[orig][dest] = TRUE;

    g->num_edges++;
    return OK;
}

Bool graph_contains(const Graph *g, long id)
{
    if (g->num_vertices == 0)
        return TRUE;

    return FALSE;
}

Vertex **graph_get_vertex(Graph *g)
{
    if (!g)
        return NULL;
    return g->vertices;
}

int graph_getNumberOfVertices(const Graph *g)
{
    return g->num_vertices;
}

int graph_getNumberOfEdges(const Graph *g)
{
    return g->num_edges;
}

Bool graph_connectionExists(const Graph *g, long orig, long dest)
{
    if ((g->connections[orig][dest]) == TRUE)
        return TRUE;

    return FALSE;
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{
    int i, counter = 0;
    if (!g || !id)
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[id][vertex_getId(g->vertices[i])] == TRUE)
        {
            counter++;
        }
    }

    return counter;
}

long *graph_getConnectionsFromId(const Graph *g, long id)
{
    int i, j = 0;

    long *arrayIDs = NULL;

    if (!(arrayIDs = calloc(graph_getNumberOfConnectionsFromId(g, id), sizeof(long))))
        return NULL;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (graph_connectionExists(g, id, vertex_getId(g->vertices[i])) == TRUE)
        {
            arrayIDs[j] = vertex_getId(g->vertices[i]);
            j++;
        }
    }

    return arrayIDs;
}

int get_vertex_from_id(const Graph *g, long id)
{
    int i;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (vertex_getId(g->vertices[i]) == id)
        {
            return i;
        }
    }
    return 0;
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag)
{
    int i, counter = 0;
    long id = 0;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (!strcmp(tag, vertex_getTag(g->vertices[i])))
        {
            id = vertex_getId(g->vertices[i]);
            i = g->num_vertices + 1;
        }
    }

    counter = graph_getNumberOfConnectionsFromId(g, id);

    return counter;
}

long *graph_getConnectionsFromTag(const Graph *g, char *tag)
{
    int i;

    long *arrayIDs = NULL, id = 0;

    if (!(arrayIDs = (long *)malloc(MAX_VTX * sizeof(long))))
        return ERROR;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (strcmp(tag, vertex_getTag(g->vertices[i])))
        {
            id = vertex_getId(g->vertices[i]);
            i = g->num_vertices + 1;
        }
    }

    arrayIDs = graph_getConnectionsFromId(g, id);

    return arrayIDs;
}

/* START [Private_functions] */
long *graph_getWhiteConnectionsFromId(const Graph *g, long id)
{
    int i, j = 0;

    long *arrayIDs = NULL;

    if (!(arrayIDs = calloc(graph_getNumberOfConnectionsFromId(g, id), sizeof(long))))
        return NULL;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (graph_connectionExists(g, id, vertex_getId(g->vertices[i])) == TRUE && vertex_getState(g->vertices[i]) == WHITE)
        {
            arrayIDs[j] = vertex_getId(g->vertices[i]);
            j++;
        }
    }

    return arrayIDs;
}

int graph_getNumberOfWhiteConnectionsFromId(const Graph *g, long id)
{
    int i, counter = 0;
    if (!g || !id)
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[id][vertex_getId(g->vertices[i])] == TRUE && vertex_getState(g->vertices[i]) == WHITE)
        {
            counter++;
        }
    }

    return counter;
}

int _graph_findVertexByTag(const Graph *g, char *tag)
{
    int i;
    for (i = 0; i < g->num_vertices; i++)
    {
        if (strcmp(g->vertices[i]->tag, tag))
        {
            return g->vertices[i]->index;
        }
    }
    return -1;
}

/*Vertex* _graph_findVertexById(const Graph * g, long id){
    int i;
    for (i = 0; i < g->num_vertices; i++)
    {
        if(g->vertices[i]->id,id){
            return g->vertices[i];
        }
    }

}*/

Status _graph_insertEdgeFromIndices(Graph *g, const long origIx, const long destIx)
{
    int i, k;

    for (i = 0; i < MAX_VTX; i++)
    {
        if (g->vertices[i]->index == origIx)
        {

            for (k = 0; k < MAX_VTX; k++)
            {
                if (g->vertices[k]->index == destIx)
                {
                    graph_newEdge(g, g->vertices[i]->id, g->vertices[k]->id);
                    return OK;
                }
            }
        }
    }

    return ERROR;
}

int _graph_getNumConnections(const Graph *g, int ix)
{
    int i, counter = 0;
    if (!g || ix < 0)
    {

        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[vertex_getId(g->vertices[ix])][vertex_getId(g->vertices[i])] == TRUE)
        {

            counter++;
        }
    }

    return counter;
}

long *_graph_getConnections(const Graph *g, int ix)
{
    int i;

    for (i = 0; i < g->num_edges; i++)
    {
        if (g->vertices[i]->index == ix)
        {
            return graph_getConnectionsFromId(g, g->vertices[i]->id);
        }
    }
    return NULL;
}

void _graph_setVertexState(Graph *g, Label l)
{
    int i;
    for (i = 0; i < g->num_vertices; i++)
    {
        g->vertices[i]->state = l;
    }
}
/* END [Private_functions] */

Status graph_breathSearch(Graph *g, long from_id, long to_id)
{
    Queue *q = NULL;
    Vertex *v = NULL;
    int i, j, index = 0, size;
    long id, *arrayIds;

    if (!g || from_id < 0 || to_id < 0)
        return ERROR;

    _graph_setVertexState(g, WHITE);

    if (!(q = queue_new()))
        return ERROR;

    for (i = 0; i < g->num_vertices; i++)
        if (vertex_getId(g->vertices[i]) == from_id)
            index = i;

    if (index < 0)
    {
        queue_free(q);
        return ERROR;
    }

    vertex_setState(g->vertices[index], BLACK);

    if (!queue_push(q, (void *)g->vertices[index]))
    {
        queue_free(q);
        return ERROR;
    }

    while (!queue_isEmpty(q))
    {
        v = (Vertex *)queue_pop(q); 
        if (!v)
        {
            queue_free(q);
            return ERROR;
        }
        vertex_print(stdout, v);
        printf("\n");
        if (vertex_getId(v) == to_id)
        {
            queue_free(q);
            return OK;
        }
        else
        {
            id = vertex_getId(v);
            arrayIds = graph_getWhiteConnectionsFromId(g, id);
            size = graph_getNumberOfWhiteConnectionsFromId(g, id);
            for (i = 0; i < size; i++)
            {
                for (j = 0; j < g->num_vertices; j++)
                    if (vertex_getId(g->vertices[j]) == arrayIds[i])
                        index = j;

                if (index < 0)
                {
                    queue_free(q);
                    return ERROR;
                }
                vertex_setState(g->vertices[index], BLACK);
                queue_push(q, (void *)g->vertices[index]);
            }
            free(arrayIds);
        }
    }

    queue_free(q);
    return ERROR;
}

Status graph_depthSearch(Graph *g, long from_id, long to_id)
{

    Vertex *v0;
    Stack *s = stack_init();
    int i;
    long id;
    int index = 0;

    if (!g || from_id < 0 || to_id < 0)
    {
        return ERROR;
    }
    _graph_setVertexState(g, WHITE);
    /*return OK;*/

    if (!s)
    {

        return ERROR;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (vertex_getId(g->vertices[i]) == from_id)
        {
            index = i;
        }
    }

    if (index < 0)
    {

        stack_free(s);
        return ERROR;
    }

    vertex_setState(g->vertices[index], BLACK);

    if (!stack_push(s, (g->vertices[index])))
    {

        stack_free(s);
        return ERROR;
    }

    while (!stack_isEmpty(s))
    {
        v0 = (Vertex *)stack_pop(s);
        if (!v0)
        {
            stack_free(s);
            return ERROR;
        }
        vertex_print(stdout, v0);
        printf("\n");
        if (vertex_getId(v0) == to_id)
        {
            stack_free(s);
            return OK;
        }
        else
        {

            id = vertex_getId(v0);
            for (i = 0; i < g->num_vertices; i++)
            {
                if (g->connections[id][vertex_getId(g->vertices[i])] && vertex_getState(g->vertices[i]) == WHITE)
                {

                    vertex_setState(g->vertices[i], BLACK);
                    stack_push(s, g->vertices[i]);
                }
            }
        }
    }

    stack_free(s);
    return ERROR;
}

int graph_print(FILE *pf, const Graph *g)
{
    int i, j, num_connections;
    long *arraysIDs = NULL;

    if (!g || !pf)
        return -1;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (!g->vertices[i])
        {
            continue;
        }

        vertex_print(pf, g->vertices[i]);
        printf(": ");
        arraysIDs = graph_getConnectionsFromId(g, vertex_getId(g->vertices[i]));
        if (!arraysIDs)
        {
            continue;
        }

        num_connections = graph_getNumberOfConnectionsFromId(g, vertex_getId(g->vertices[i]));
        /*num_connections = _graph_getNumConnections(g, i);*/
        for (j = 0; j < num_connections; j++)
        {

            vertex_print(pf, g->vertices[get_vertex_from_id(g, arraysIDs[j])]);
        }
        printf("\n");
        free(arraysIDs);
    }

    return i;
}

Status graph_readFromFile(FILE *fin, Graph *g)
{
    int i, j, counter;
    long id1 = 0, id2 = 0;
    char str[100];

    if (!fin)
    {
        fprintf(stderr, "Error1");
        return ERROR;
    }

    if (fscanf(fin, "%i", &counter) != 1)
    {
        fprintf(stderr, "Error: Failed to read the number of vertices\n");
        return ERROR;
    }

    if (!fgets(str, 100, fin))
    {
        fprintf(stderr, "Error: Failed to read newline after vertex count\n");
        return ERROR;
    }

    for (i = 0; i < counter; i++)
    {
        if (!fgets(str, 100, fin))
        {
            fprintf(stderr, "Error: Failed to read vertex description\n");
            return ERROR;
        }

        for (j = 0; j < 100; j++)
        {
            if (str[j] == '\n')
            {
                str[j] = '\0';
                break;
            }
        }

        if (graph_newVertex(g, str) == ERROR)
        {
            fprintf(stderr, "Error: Failed to add vertex\n");
            return ERROR;
        }
    }

    for (i = 0; i < 8; i++)
    {
        if (fscanf(fin, "%ld %ld", &id1, &id2) != 2)
        {
            fprintf(stderr, "Error: Failed to read edge %d\n", i + 1);
            return ERROR;
        }

        if (graph_newEdge(g, id1, id2) == ERROR)
        {
            fprintf(stderr, "Error: Failed to add edge (%ld -> %ld)\n", id1, id2);
            return ERROR;
        }
    }

    fclose(fin);

    return OK;
}