// src/ft_dg.c

#include <stdlib.h>
#include <string.h>

#include "ft_dg.h"

ft_dg_status_t ft_dg_create(ft_dg_t* g, const ft_dg_edge_t* edges, const ft_dg_size_t max_nodes, const ft_dg_size_t max_edges) { // 建图（CSR）
    g -> num_nodes = max_nodes;
    g -> num_edges = max_edges;
    g -> offsets = (ft_dg_size_t*) calloc(max_nodes + 1, sizeof(ft_dg_size_t));
    g -> edges = (ft_dg_size_t*) calloc(max_edges, sizeof(ft_dg_size_t));
    if (! g -> offsets || ! g -> edges) {  // 内存不足
        free(g -> offsets);
        free(g -> edges);
        return FT_DG_OUT_OF_MEMORY;
    }

    // 统计出度，前缀和地构建数组 offsets
    for (ft_dg_size_t i = 0; i < max_edges; i ++) {
        g -> offsets[edges[i].u + 1] ++;
    }
    for (ft_dg_size_t i = 1; i <= max_nodes; i ++) {
        g -> offsets[i] += g -> offsets[i - 1];
    }

    // 填 edges
    ft_dg_size_t* cursor = (ft_dg_size_t*) malloc((max_nodes + 1) * sizeof(ft_dg_size_t));
    memcpy(cursor, g -> offsets, (max_nodes + 1) * sizeof(ft_dg_size_t));
    for (ft_dg_size_t i = 0; i < max_edges; i ++) {
        g -> edges[cursor[edges[i].u]] = edges[i].v;
        cursor[edges[i].u] ++;
    }
    free(cursor);
    cursor = NULL;

    return FT_DG_OK;
}

void ft_dg_free(ft_dg_t* g) {
    g -> num_nodes = 0;
    g -> num_edges = 0;
    free(g -> offsets);
    g -> offsets = NULL;
    free(g -> edges);
    g -> edges = NULL;

    return;
}
