// src/main.c

#include <stdio.h>

#include "ft_ht.h"

int main() {
    ft_ht_t ht;
    ft_ht_create(&ht, 16);

    int keys[] = {42, 17, 88, 33};
    for (int i = 0; i < 4; i ++) {
        ft_ht_status_t s = ft_ht_insert(& ht, & keys[i], sizeof(int), keys[i] * 100);
        printf("insert %d: %d\n", keys[i], s);
    }

    for (int i = 0; i < 4; i ++) {
        ft_ht_size_t val;
        ft_ht_status_t s = ft_ht_find(& ht, & keys[i], sizeof(int), & val);
        printf("lookup %d: status=%d, value=%zu\n", keys[i], s, val);
    }

    ft_ht_free(& ht);

    return 0;
}
