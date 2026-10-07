// include/ft_ht.h

#ifndef FT_HT_H
#define FT_HT_H

#include <stddef.h>
#include <stdint.h>

#define XXH_INLINE_ALL
#include "xxhash.h"

#define FT_HT_MAX_KEY_BYTES 64
#define LOAD_FACTOR 0.75  // 负载因子

typedef size_t ft_ht_size_t;
typedef uint8_t ft_ht_byte_t;

static inline XXH64_hash_t ft_ht_hash(const void* buffer, ft_ht_size_t size) {  // 哈希函数
    return XXH3_64bits(buffer, (size_t) size);
}

typedef enum {
    TRUE = 1,
    FALSE = 0
} ft_ht_bool_t;

typedef struct {
    ft_ht_byte_t key[FT_HT_MAX_KEY_BYTES];  
    ft_ht_size_t value;
    ft_ht_bool_t occupied;
} ft_ht_slot_t;

typedef struct {
    ft_ht_slot_t* slots;  // 槽数组
    ft_ht_size_t capacity;  // 最大容量
    ft_ht_size_t count;  // 当前已用
} ft_ht_t;

typedef enum {
    FT_HT_OK = 0,
    FT_HT_FULL,
    FT_HT_EXISTS,  // 键被重复定义
    FT_HT_NOT_FOUND,  // 未找到键
    FT_HT_OUT_OF_MEMORY  // 内存不足
} ft_ht_status_t;

ft_ht_status_t ft_ht_create(ft_ht_t* ht, ft_ht_size_t capacity);
void ft_ht_free(ft_ht_t* ht);
ft_ht_status_t ft_ht_find(const ft_ht_t* ht, const void* key, const ft_ht_size_t key_len, ft_ht_size_t* value);
ft_ht_status_t ft_ht_insert(ft_ht_t* ht, const void* key, const ft_ht_size_t key_len, const ft_ht_size_t value);

#endif
