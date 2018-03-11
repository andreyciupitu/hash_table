#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "list.h"
#include "utils.h"

hash_table *new_hash_table(unsigned int size, hash_func hash)
{
	unsigned int i;
	hash_table *table;

	/*
	 * Allocate a new hash_table struct
	 */
	table = malloc(sizeof(hash_table));
	DIE(table == NULL, "Memory alloc error in hash initialization");

	/*
	 * Initialize struct fields
	 */
	table->buckets = malloc(size * sizeof(list));
	DIE(table->buckets == NULL,
		"Memory alloc error in hash initialization");
	table->size = size;
	table->hash = hash;

	/*
	 * Initialize buckets
	 */
	for (i = 0; i < size; i++)
		init_list(&table->buckets[i]);

	return table;
}

void add_to_hash_table(hash_table *table, char *data)
{
	unsigned int bucket;

	bucket = table->hash(data, table->size);

	/*
	 * Don't allow duplicates
	 */
	if (!contains_element(table->buckets[bucket], data))
		add_element(table->buckets[bucket], data);
}

void remove_from_hash_table(hash_table *table, char *data)
{
	unsigned int bucket;

	bucket = table->hash(data, table->size);
	remove_element(table->buckets[bucket], data);
}

int contained_in_hash_table(hash_table *table, char *data)
{
	unsigned int bucket;

	bucket = table->hash(data, table->size);
	return contains_element(table->buckets[bucket], data);
}

hash_table *resize_hash_table(hash_table *table, unsigned int size)
{
	unsigned int i;
	hash_table *new_table;
	struct node *it;

	/*
	 * Create a new hash table with the new size
	 */
	new_table = new_hash_table(size, table->hash);

	for (i = 0; i < table->size; i++) {
		/*
		 * Rehash the elements
		 */
		it = table->buckets[i]->next;
		while (it != NULL) {
			add_to_hash_table(new_table, it->data);
			it = it->next;
		}
	}

	/*
	 * Destroy the old table
	 */
	destroy_hash_table(table);
	return new_table;
}

void clear_hash_table(hash_table *table)
{
	unsigned int i;

	for (i = 0; i < table->size; i++)
		clear_list(table->buckets[i]);
}

void destroy_hash_table(hash_table *table)
{
	unsigned int i;

	/*
	 * Destroy the buckets first
	 */
	for (i = 0; i < table->size; i++)
		destroy_list(&table->buckets[i]);
	free(table->buckets);

	free(table);
}

void print_bucket(hash_table *table, unsigned int index, FILE *output_file)
{
	/*
	 * Check for invalid index
	 */
	CUSTOM_DIE(index > table->size, "Invalid index size",
		INVALID_COMMAND);

	print_list(table->buckets[index], output_file);
}

void print_hash_table(hash_table *table, FILE *output_file)
{
	unsigned int i;

	for (i = 0; i < table->size; i++)
		print_list(table->buckets[i], output_file);
}
