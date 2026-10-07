// src/ft_dg.c

#include <stdlib.h>
#include <string.h>

#include "ft_dg.h"

ft_dg_status_t ft_dg_create(ft_dg_t* g, const ft_dg_edge_t* edges, const ft_dg_size_t max_nodes, const ft_dg_size_t max_edges) { // 建图（CSR）
    g -> num_nodes = max_nodes;
    g -> num_edges = max_edges;
    g -> offsets = (ft_dg_size_t*) calloc(max_nodes + 1, sizeof(ft_dg_size_t));
    g -> edges = (ft_dg_size_t*) calloc(max_edges, sizeof(ft_dg_size_t));
    g -> indegree = (ft_dg_size_t*) calloc(max_nodes, sizeof(ft_dg_size_t));
    g -> outdegree = (ft_dg_size_t*) calloc(max_nodes, sizeof(ft_dg_size_t));
    if (! g -> offsets || ! g -> edges || ! g -> indegree || ! g -> outdegree) {  // 内存不足
        free(g -> offsets);
        free(g -> edges);
        free(g -> indegree);
        free(g -> outdegree);
        g -> offsets = NULL;
        g -> edges = NULL;
        g -> indegree = NULL;
        g -> outdegree = NULL;

        return FT_DG_OUT_OF_MEMORY;
    }

    // 统计入度
    for (ft_dg_size_t i = 0; i < max_edges; i ++) {
        g -> indegree[edges[i].v] ++;
    }

    // 统计出度
    for (ft_dg_size_t i = 0; i < max_edges; i ++) {
        g -> outdegree[edges[i].u] ++;
    }

    // 前缀和地构建数组 offsets
    for (ft_dg_size_t i = 0; i < max_nodes - 1; i ++) {
        g -> offsets[i + 1] = g -> offsets[i] + g -> outdegree[i];
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
    free(g -> edges);
    free(g -> indegree);
    free(g -> outdegree);
    g -> offsets = NULL;
    g -> edges = NULL;
    g -> indegree = NULL;
    g -> outdegree = NULL;

    return;
}

ft_dg_status_t ft_dg_toposort(const ft_dg_t* g, ft_dg_size_t* sorted, ft_dg_size_t* len) {  // Kann 拓扑排序算法
    ft_dg_size_t* indeg = malloc(g -> num_nodes * sizeof(ft_dg_size_t));
    memcpy(indeg, g -> indegree, g -> num_nodes * sizeof(ft_dg_size_t));
    
    // 队列
    ft_dg_size_t* queue = malloc(g -> num_nodes * sizeof(ft_dg_size_t));
    ft_dg_size_t front = 0, back = 0;
    
    // 入度为 0 的节点入队
    for (ft_dg_size_t i = 0; i < g -> num_nodes; i ++) {
        if (indeg[i] == 0) queue[back ++] = i;
    }
    
    // 主循环
    ft_dg_size_t cnt = 0;
    while (front < back) {
        ft_dg_size_t u = queue[front ++];
        sorted[cnt ++] = u;
        
        for (ft_dg_size_t i = g -> offsets[u]; i < g -> offsets[u + 1]; i ++) {
            ft_dg_size_t v = g -> edges[i];
            indeg[v] --;
            if (indeg[v] == 0) {
                queue[back ++] = v;
            }
        }
    }
    
    free(indeg);
    free(queue);
    
    * len = cnt;
    return cnt == g -> num_nodes ? FT_DG_OK : FT_DG_CYCLE;
}
