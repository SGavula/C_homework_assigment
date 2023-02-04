#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include "graph_utils.h"

int load_graph_simple(const char *fname, graph_t *graph) 
{
   char c;
   int e = 0;
   int from = 0;
   int to = 0;
   int cost = 0;
   int field = 0;
   int i = 0;
   // Open the file
    int fd = open(fname, O_RDONLY, S_IRUSR | S_IWUSR);

    // Get the size of the file
    struct stat sb;
    if(fstat(fd, &sb) == -1) {
      perror("Cannot get file size\n.");
    }
    off_t size = sb.st_size;

    // Memory map the file
    char *p = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Read from the file through the memory map
    for (off_t i = 0; i < size; i++) {
        putchar(p[i]);
    }

    // Unmap the file and close it
    munmap(p, size);
    close(fd);

   // if((file = fopen(fname, "r")) == NULL) {
   //      fprintf(stderr, "Cannot open the file.\n");
   //      free(graph->edges);
   //      free(graph);
   //      exit(ERR_FILE);
   //  }

   // graph = enlarge_graph_utils(graph);

   // while(feof(file) != 1) {
   //    c = fgetc(file);
   //    if (c >= '0' && c <= '9') {
   //       // Add the numeric value of the character to the current field value
   //       //- '0' because we want convert c to string
   //       if (field == 0) {
   //             from = from * 10 + (c - '0');
   //       } else if (field == 1) {
   //             to = to * 10 + (c - '0');
   //       } else if (field == 2) {
   //             cost = cost * 10 + (c - '0');
   //       }
   //    } else if (c == ' ') {
   //       // Move to the next field when a space is encountered
   //       field++;
   //    }else {
   //       if(feof(file) != 1) {
   //             graph->num_edges++;
   //             e++;
   //             if(graph->num_edges >= graph->capacity){
   //                graph = enlarge_graph_utils(graph);
   //             }
   //             graph->edges[i].from = from;
   //             graph->edges[i].to = to;
   //             graph->edges[i].cost = cost;
   //             i++;
   //             field = 0;
   //             from = 0;
   //             to = 0;
   //             cost = 0;
   //       }
   //    }
   // }

   // if (file) {
   //    fclose(file);
   // }
   return e;
}
