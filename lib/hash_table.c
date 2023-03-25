#include <stdlib.h>
#include <string.h>

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

hash_table *create_hash_table(size_t size) {
    hash_table *table = malloc(sizeof(hash_table));
    table->entries = (hash_table**)malloc(sizeof(hash_table_entry*) * size);
    table->size    = size;
    table->count   = 0;
    return table;
}

void hash_table_free(hash_table *table) {
    for (size_t i = 0; i < table->size; i++) {
        hash_table_entry *entry = table->entries[i];
        while (entry != NULL) {
            hash_table_entry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(table->entries);
    free(table);
}

void hash_table_set(hash_table *table, char *key, void *value) {
    size_t index = hash(key) % table->size;
    hash_table_entry *entry = table->entries[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }
    entry = malloc(sizeof(hash_table_entry));
    entry->key = strdup(key);
    entry->value = value;
    entry->next = table->entries[index];
    table->entries[index] = entry;
    table->count++;
}

void *hash_table_get(hash_table *table, char *key) {
    size_t index = hash(key) % table->size;
    hash_table_entry *entry = table->entries[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void hash_table_delete(hash_table *table, char *key) {
    size_t index = hash(key) % table->size;
    hash_table_entry *entry = table->entries[index];
    hash_table_entry *prev = NULL;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            if (prev == NULL) {
                table->entries[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry->key);
            free(entry);
            table->count--;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}