#ifndef HASH_TABLE_H
#define HASH_TABLE_H 1

#include <stdio.h>

#include "list.h"

typedef struct hash_table {
	list *buckets;
	int size;
} hash_table;

void init_hash_table(hash_table *table, int size);
void destroy_hash_table(hash_table *table);

void add_to_hash_table(hash_table *table, char *data);
void remove_from_hash_table(hash_table *table, char *data);
int contained_in_hash_table(hash_table *table, char *data);

void clear_hash_table(hash_table *table);
void resize_hash_table(hash_table *table, int size);

int print_bucket(hash_table *table, int index, FILE *output_file);
void print_hash_table(hash_table *table, FILE *output_file);

#endif // HASH_TABLE_H
