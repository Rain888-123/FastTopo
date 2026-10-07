// src/main.c

#include <stdio.h>

#include "ft_dg.h"

int main(void) {
    ft_dg_edge_t edges[] = {
        {0, 1},
        {0, 2},
        {1, 2},
        {1, 3},
        {2, 3},
        {3, 1},
        {0, 3},
    };
    ft_dg_size_t num_nodes = 4;
    ft_dg_size_t num_edges = 7;

    ft_dg_t g;
    ft_dg_status_t status = ft_dg_create(&g, edges, num_nodes, num_edges);
    if (status != FT_DG_OK) {
        printf("ft_dg_create failed: %d\n", status);
        return 1;
    }

    printf("Graph created: %zu nodes, %zu edges\n", g.num_nodes, g.num_edges);
    printf("Indegrees: ");
    for (ft_dg_size_t i = 0; i < g.num_nodes; i ++) {
        printf("%zu ", g.indegree[i]);
    }
    printf("\n");
    printf("Outdegrees: ");
    for (ft_dg_size_t i = 0; i < g.num_nodes; i ++) {
        printf("%zu ", g.outdegree[i]);
    }
    printf("\n");

    // 拓扑排序
    ft_dg_size_t sorted[num_nodes];
    ft_dg_size_t len;
    status = ft_dg_toposort(& g, sorted, & len);
    if (status == FT_DG_OK) {
        printf("Topological sort: ");
        for (ft_dg_size_t i = 0; i < len; i ++) {
            printf("%zu ", sorted[i]);
        }
        printf("\n");
    } 
    else {
        printf("Graph has a cycle!\n");
    }

    ft_dg_free(& g);

    return 0;
}
