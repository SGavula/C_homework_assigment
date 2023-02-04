#ifndef __GRAPH_UTILS_H__
#define __GRAPH_UTILS_H__

#include "graph.h"

graph_t* allocate_graph_utils(void);

void free_graph_utils(graph_t **g);

graph_t* enlarge_graph_utils(graph_t *g);

void print_graph(graph_t *g);

#endif
