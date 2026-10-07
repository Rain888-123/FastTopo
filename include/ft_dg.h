// include/ft_dg.h

#ifndef FT_DG_H
#define FT_DG_H

#include <stddef.h>

typedef size_t ft_dg_size_t;

typedef struct {
    ft_dg_size_t n;  // 节点数
    ft_dg_size_t m;  // 边数

    ft_dg_size_t* offsets;  // 长度 n+1
    ft_dg_size_t* edges;  // 长度 m，存终点索引

    ft_dg_size_t max_nodes;
    ft_dg_size_t max_edges;
} ft_dg_t;  // 有向图

typedef enum {
    FT_DG_OK = 0,
    FT_DG_FULL,
    FT_DG_OUT_OF_MEMORY,  // 内存不足
    FT_DG_MULTI_EDGES,  // 重边
    FT_DG_SELF_LOOP  // 自环
} ft_dg_status_t;

ft_dg_status_t ft_dg_create(ft_dg_t* g, ft_dg_size_t max_nodes, ft_dg_size_t max_edges);
void ft_dg_free(ft_dg_t* g);
ft_dg_status_t ft_dg_add_edge(ft_dg_t* g, ft_dg_size_t u, ft_dg_size_t v);

#endif
