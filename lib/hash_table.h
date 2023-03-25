#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>

typedef struct hash_table_entry {
    char *key;
    void *value;
    struct hash_table_entry *next;
} hash_table_entry;

typedef struct hash_table {
    hash_table_entry **entries;
    size_t size;
    size_t count;
} hash_table;

hash_table *create_hash_table(size_t size);
void hash_table_free(hash_table *table);
void hash_table_set(hash_table *table, char *key, void *value);
void *hash_table_get(hash_table *table, char *key);
void hash_table_delete(hash_table *table, char *key);

#endif // HASH_TABLE_H