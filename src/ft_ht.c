// src/ft_ht.c

#include <stdlib.h>
#include <string.h>

#include "ft_ht.h"

ft_ht_status_t ft_ht_create(ft_ht_t* ht, ft_ht_size_t max_elements) {
    ft_ht_size_t capacity = (ft_ht_size_t) (max_elements / LOAD_FACTOR) + 1;  // 计算最佳容量

    ht -> slots = (ft_ht_slot_t*) calloc(capacity, sizeof(ft_ht_slot_t));
    if (! ht -> slots) {
        return FT_HT_OUT_OF_MEMORY;
    }
    ht -> capacity = capacity;
    ht -> count = 0;

    return FT_HT_OK;
}

void ft_ht_free(ft_ht_t* ht) {
    free(ht -> slots);
    ht -> slots = NULL;  // 安全释放
    ht -> capacity = 0;
    ht -> count = 0;

    return;
}

ft_ht_status_t ft_ht_find(const ft_ht_t* ht, const void* key, const ft_ht_size_t key_len, ft_ht_size_t* value) {
    ft_ht_size_t idx = ft_ht_hash(key, key_len) % ht -> capacity;

    while (ht -> slots[idx].occupied == TRUE) {  // 查找键
        if (! memcmp(key, ht -> slots[idx].key, key_len)) {  // 比较键是否相等
            * value = ht -> slots[idx].value;

            return FT_HT_OK;
        }
        idx = (idx + 1) % ht -> capacity;  // 线性探测
    }
    
    return FT_HT_NOT_FOUND;
}

ft_ht_status_t ft_ht_insert(ft_ht_t* ht, const void* key, const ft_ht_size_t key_len, const ft_ht_size_t value) {
    if (ht -> capacity == ht -> count) return FT_HT_FULL;  // 表已满
    
    ft_ht_size_t idx = ft_ht_hash(key, key_len) % ht -> capacity;

    while (ht -> slots[idx].occupied == TRUE) {  // 查找键
        if (! memcmp(key, ht -> slots[idx].key, key_len)) {  // 比较键是否相等
            return FT_HT_EXISTS;
        }
        idx = (idx + 1) % ht -> capacity;  // 线性探测
    }
    
    memcpy(ht -> slots[idx].key, key, key_len);
    ht -> slots[idx].value = value;
    ht -> slots[idx].occupied = TRUE;
    ht -> count ++;

    return FT_HT_OK;
}
