#include "dijkstra.c"

#include <stdio.h>

int main(int argc, char *argv[]) 
{
   int ret = 0;
   int array[23][3] = {
      {0, 1, 4},
      {0, 3, 85},
      {1, 0, 74},
      {1, 2, 18},
      {1, 4, 12},
      {2, 1, 12},
      {2, 5, 74},
      {2, 9, 12},
      {3, 4, 32},
      {3, 6, 38},
      {4, 3, 66},
      {4, 5, 76},
      {4, 7, 33},
      {5, 9, 21},
      {5, 8, 11},
      {6, 7, 10},
      {6, 3, 12},
      {7, 6, 2},
      {7, 8, 72},
      {8, 7, 18},
      {8, 5, 31},
      {8, 9, 78},
      {9, 5, 8},
   };

   int array2[15][3] = {
      {0, 1, 4},
      {0, 3, 85},
      {1, 0, 74},
      {1, 2, 18},
      {1, 4, 12},
      {2, 1, 12},
      {2, 5, 74},
      {2, 9, 12},
      {6, 3, 12},
      {7, 6, 2},
      {7, 8, 72},
      {8, 7, 18},
      {8, 5, 31},
      {8, 9, 78},
      {9, 5, 8}
   };

   if (argc < 3) {
      fprintf(stderr, "Call as\n %s graph_file solution_file\n", argv[0]);
   } else {
      fprintf(stderr, "Load graph from %s\n", argv[1]);
      void *dij = dijkstra_init();
      dijkstra_set_graph(23 ,array, dij);
      fprintf(stderr, "Find all shortest paths from the node 0\n");
      dijkstra_solve(dij, 0);
      fprintf(stderr, "Save solution to %s\n", argv[2]);
      dijkstra_save_path(dij, argv[2]);
      fprintf(stderr, "Free allocated memory\n");
      dijkstra_free(dij);
      ret = 0;
   }
   return ret;
}

/* end of tgraph_search.c */
