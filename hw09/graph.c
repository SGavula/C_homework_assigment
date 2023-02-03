#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/* This is a testing file just to be able to compile the 
 * examples of binary files to convert graph from txt->bin
 * and bin -> txt
 */

// - function -----------------------------------------------------------------
graph_t* allocate_graph() {
    //Malloc graph struct on the heap
    graph_t* graph = malloc(sizeof(graph_t));
    if(graph == NULL) {
        fprintf(stderr, "Error: malloc\n");
        return NULL;
    }

    //Malloc pointer array for edges
    edge_t* e = malloc(sizeof(edge_t) * INIT_SIZE);
    if(e == NULL) {
        fprintf(stderr, "Error: malloc\n");
        return NULL;
    }

    graph->edges = e;
    graph->num_of_edges = 0;
    graph->capacity = INIT_SIZE;
    return graph;
}

graph_t* enlarge_graph(graph_t* graph) {
    graph->capacity = graph->capacity * 2;

    edge_t* tmp = realloc(graph->edges, sizeof(edge_t) * graph->capacity);
    if(tmp == NULL) {
        fprintf(stderr, "Error: Realloc.\n");
        return NULL;
    }
    graph->edges = tmp;
    return graph;
}

// - function -----------------------------------------------------------------
void free_graph(graph_t **graph) {
    //Free memory
    if((*graph)->capacity > 0) {
        free((*graph)->edges);
    }
    free(*graph);
    *graph = NULL;
}

// - function -----------------------------------------------------------------
/* Load a graph from the text file. */
void load_txt(const char *fname, graph_t *graph) {
    char c;
    int from = 0;
    int to = 0;
    int cost = 0;
    int field = 0;
    int i = 0;

    FILE *file;
    if((file = fopen(fname, "r")) == NULL) {
        fprintf(stderr, "Cannot open the file.\n");
        free(graph->edges);
        free(graph);
        exit(ERR_FILE);
    }

    while(feof(file) != 1) {
        c = fgetc(file);
        if (c >= '0' && c <= '9') {
            // Add the numeric value of the character to the current field value
            //- '0' because we want convert c to string
            if (field == 0) {
                from = from * 10 + (c - '0');
            } else if (field == 1) {
                to = to * 10 + (c - '0');
            } else if (field == 2) {
                cost = cost * 10 + (c - '0');
            }
        } else if (c == ' ') {
            // Move to the next field when a space is encountered
            field++;
        }else {
            if(feof(file) != 1) {
                graph->num_of_edges++;
                if(graph->num_of_edges >= graph->capacity){
                    graph = enlarge_graph(graph);
                }
                graph->edges[i].from = from;
                graph->edges[i].to = to;
                graph->edges[i].cost = cost;
                i++;
                field = 0;
                from = 0;
                to = 0;
                cost = 0;
            }
        }
    }

    fclose(file);
}

// - function -----------------------------------------------------------------
/* Load a graph from the binary file. */
void load_bin(const char *fname, graph_t *graph) {
    FILE* file;
    file = fopen(fname, "rb");
    if(file == NULL) {
        fprintf(stderr, "Cannot open the file.\n");
        exit(ERR_FILE);
    }

    // read file contents till end of file
    while(fread(&graph->edges[graph->num_of_edges], sizeof(edge_t), 1, file)) {
        graph->num_of_edges++;
        if(graph->num_of_edges >= graph->capacity){
            graph = enlarge_graph(graph);
        }
    }

   fclose(file);
}

// - function -----------------------------------------------------------------
void save_txt(const graph_t * const graph, const char *fname) {
    FILE* file;
    file = fopen(fname, "w");
    if(file == NULL) {
      fprintf(stderr, "Cannot open the file.\n");
      exit(ERR_FILE);
    }


   for(int i = 0; i < graph->num_of_edges; i++) {
      fprintf(file, "%i %i %i\n", graph->edges[i].from, graph->edges[i].to, graph->edges[i].cost);
   }
    
    fclose(file);
}

// - function -----------------------------------------------------------------
void save_bin(const graph_t * const graph, const char *fname) {
    FILE* file;
    file = fopen(fname, "wb");
    if(file == NULL) {
        fprintf(stderr, "Cannot open the file.\n");
        exit(ERR_FILE);
    }

    fwrite(graph->edges, sizeof(edge_t), graph->num_of_edges, file);
    fclose(file);
}
