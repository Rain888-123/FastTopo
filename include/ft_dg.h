// include/ft_dg.h

#ifndef FT_DG_H
#define FT_DG_H

#include <stddef.h>

typedef size_t ft_dg_size_t;

typedef struct {
    ft_dg_size_t u;
    ft_dg_size_t v;
} ft_dg_edge_t;


typedef struct {
    ft_dg_size_t num_nodes;  // 节点数
    ft_dg_size_t num_edges;  // 边数

    ft_dg_size_t* offsets;  // 长度 num_nodes + 1
    ft_dg_size_t* edges;  // 长度 num_edges，存终点索引

    ft_dg_size_t* indegree;
    ft_dg_size_t* outdegree;
} ft_dg_t;  // 有向图

typedef enum {
    FT_DG_OK = 0,
    FT_DG_OUT_OF_MEMORY,  // 内存不足
    FT_DG_CYCLE  // 检测到环
} ft_dg_status_t;

ft_dg_status_t ft_dg_create(ft_dg_t* g, const ft_dg_edge_t* edges, const ft_dg_size_t max_nodes, const ft_dg_size_t max_edges);
void ft_dg_free(ft_dg_t* g);
ft_dg_status_t ft_dg_toposort(const ft_dg_t* g, ft_dg_size_t* sorted, ft_dg_size_t* len);

#endif
