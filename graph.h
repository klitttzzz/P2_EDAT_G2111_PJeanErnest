/**
 * @file graph.h
 * @author Profesores Prog2
 * @date Created on February 07, 2021
 * @version 1.0
 * @brief Library to manage the Graph ADT
 *
 * @see
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"

typedef struct _Graph Graph;

/**
 * @brief Creates a new empty graph.
 *
 * Allocates memory for a new graph and initializes it to be empty 
 * (no vertices and no edges).
 *
 * @return A pointer to the graph if it was correctly allocated, 
 * NULL otherwise.
 **/
Graph * graph_init();

/**
 * @brief Frees a graph.
 *
 * Frees all the memory allocated for the graph.
 *
 * @param g Pointer to graph to be freed.
 **/
void graph_free(Graph *g);

/**
 * @brief Inserts a new vertex in a graph.
 *
 * Creates a vertex by calling vertex_initFromString and adds it to
 * a graph. If a vertex with the same id already exists in the graph, 
 * it is not added. 
 *
 * @param g Pointer to the graph.
 * @param desc Description of the vertex.
 *
 * @return Returns OK if the vertex could be created (or if it exists 
 * already), ERROR otherwise.
 **/
Status graph_newVertex(Graph *g, char *desc);

/**
 * @brief Creates an edge between to vertices of a graph.
 *
 * If any of the two vertices does not exist in the graph the edge is
 * not created.
 *
 * @param g Pointer to the graph.
 * @param orig ID of the origin vertex.
 * @param dest ID of the destination vertex.
 *
 * @return OK if the edge could be added to the graph, ERROR otherwise.
 **/
Status graph_newEdge(Graph *g, long orig, long dest);

/**
 * @brief Checks if a graph contains a vertex.
 *
 * @param g Pointer to the graph.
 * @param id ID of the vertex.
 *
 * @return Returns TRUE if there is a vertex in the graph g with the
 * ID id, FALSE otherwise.
 **/
Bool graph_contains(const Graph *g, long id);

/**
 * @brief Returns the total number of vertices in a graph.
 *
 * @param g Pointer to the graph.
 *
 * @return Returns The number of vertices in the graph, or -1 if 
 * there is any error.
 **/
int graph_getNumberOfVertices(const Graph *g);

/**
 * @brief Returns the total number of edges  * in the graph.
 *
 * @param g Pointer to the graph.
 *
 * @return Returns The number of vertices in the graph, or -1 if 
 * there is any error.
 **/
int graph_getNumberOfEdges(const Graph *g);


/**
 * @brief Retrieves the vertex index corresponding to a given vertex ID in the graph.
 *
 * @param g Pointer to the Graph structure.
 * @param id The ID of the vertex to search for.
 * @return The index of the vertex in the graph if found, or -1 if the vertex ID does not exist.
 */
int get_vertex_from_id(const Graph *g, long id);

/**
 * @brief Determines if there is a connection between a pair of vertices.
 *
 * @param g Pointer to the graph.
 * @param orig ID of the origin vertex.
 * @param dest ID of the destination vertex.
 *
 * @return Returns TRUE if there is a connection in g from orig
 *  to dest, FALSE otherwise.
 **/
Bool graph_connectionExists(const Graph *g, long orig, long dest);


/**
 * @brief Retrieves the array of vertices from the graph.
 *
 * This function returns a pointer to an array of vertices that belong to the given graph.
 *
 * @param g A pointer to the Graph structure.
 * @return A pointer to an array of Vertex pointers representing the vertices in the graph.
 */
Vertex** graph_get_vertex(Graph *g);

/**
 * @brief Gets the number of connections starting at a given vertex.
 *
 * @param g Pointer to the graph.
 * @param id ID of the origin vertex.
 *
 * @return Returns the total number of connections starting at 
 * vertex with ID id, or -1 if there is any error.
 **/
int graph_getNumberOfConnectionsFromId(const Graph *g, long id);

/**
 * @brief Returns an array with the ids of all the vertices which a 
 * given vertex connects to.
 *
 * This function allocates memory for the array.
 *
 * @param g Pointer to the graph.
 * @param id ID of the origin vertex.
 *
 * @return Returns an array with the ids of all the vertices to which 
 * the vertex with ID id is connected, or NULL if there is any error.
 */
long *graph_getConnectionsFromId(const Graph *g, long id);

/**
 * @brief Gets the number of connections starting at a given vertex.
 *
 * @param g Pointer to the graph.
 * @param tag Tag of the origin vertex.
 *
 * @return Returns the total number of connections starting at 
 * vertex with Tag tag, or -1 if there is any error.
 **/
int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag);

/**
 * @brief Returns an array with the ids of all the vertices which a 
 * given vertex connects to.
 *
 * This function allocates memory for the array.
 *
 * @param g Pointer to the graph.
 * @param tag Tag of the origin vertex.
 *
 * @return Returns an array with the ids of all the vertices to which 
 * the vertex with Tag tag is connected, or NULL if there is any error.
 */
long *graph_getConnectionsFromTag(const Graph *g, char *tag);

/**
 * @brief: Makes a search from the origin vertex to the destination vertex of a
graph using the breath-first search algorithm
 * using an ADT Stack
 *
 * The function prints each visited vertex while traversing the graph
 *
 * @param g, Pointer to graph
 * @param from_id, id of the origin Vertex
 * @param to_id, id of the destination Vertex
 * @return The function returns OK or ERROR
**/
Status graph_breathSearch (Graph *g, long from_id, long to_id);

/**
 * @brief: Makes a search from the origin vertex to the destination vertex of a
graph using the depth-first search algorithm
 * using an ADT Stack
 *
 * The function prints each visited vertex while traversing the graph
 *
 * @param g, Pointer to graph
 * @param from_id, id of the origin Vertex
 * @param to_id, id of the destination Vertex
 * @return The function returns OK or ERROR
**/
Status graph_depthSearch (Graph *g, long from_id, long to_id);
/**
 * @brief Prints a graph.
 *
 * Prints the graph g to the file pf.
 * The format to be followed is: print a line by vertex with the 
 * information associated with the vertex and the id of their connections:
 *
 * For example:
 * [1, Madrid, 0]: [2, Toledo, 0] [3, Avila, 0] 
 * [2, Toledo, 0]: [4, Segovia, 0] 
 * [3, Avila, 0]: 
 * [4, Segovia, 0]: [3, Avila, 0]
 *
 * @param pf File descriptor.
 * @param g Pointer to the graph.
 *
 * @return The number of characters printed, or -1 if there is any error.
 */
int graph_print (FILE *pf, const Graph *g);


/**
 * @brief Reads a graph definition from a text file.
 *
 * Reads a graph description from the text file pointed to by fin,
 * and fills the graph g.
 *
 * The first line in the file contains the number of vertices.
 * Then one line per vertex with the vertex description.  
 * Finally one line per connection, with the ids of the origin and 
 * the destination. 
 *
 * For example:
 *
 * 4
 * id:1 tag:Madrid
 * id:2 tag:Toledo
 * id:3 tag:Avila
 * id:4 tag:Segovia
 * 1 2
 * 1 3
 * 2 4
 * 4 3
 *
 * @param fin Pointer to the input stream.
 * @param g Pointer to the graph.
 *
 * @return OK or ERROR
 */
Status graph_readFromFile (FILE *fin, Graph *g);

#endif /* GRAPH_H */