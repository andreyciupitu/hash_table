#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "list.h"

int hash(char *data, unsigned int cacat)
{
	return strlen(data) % cacat;
}

void init_hash_table(hash_table *table, int size)
{
	int i;
	table->buckets = (list*)malloc(size * sizeof(list));
	table->size = size;
	for (i = 0; i < size; i++)
		init_list(&table->buckets[i]);
}

void add_to_hash_table(hash_table *table, char *data)
{
	if (!contains_element(table->buckets[hash(data, table->size)], data))
		add_element(table->buckets[hash(data, table->size)], data);
}

void remove_from_hash_table(hash_table *table, char *data)
{
	remove_element(table->buckets[hash(data, table->size)], data);
}

int contained_in_hash_table(hash_table *table, char *data)
{
	return contains_element(table->buckets[hash(data, table->size)], data);
}

void resize_hash_table(hash_table *table, int size)
{
	int i;
	hash_table new_table;
	init_hash_table(&new_table, size);
	for (i = 0; i < table->size; i++)
	{
		struct node *it = table->buckets[i]->next;
		while (it != NULL)
		{
			add_to_hash_table(&new_table, it->data);
			it = it->next;
		}
	}
	destroy_hash_table(table);
	*table = new_table;
}

void clear_hash_table(hash_table *table)
{
	int i;
	for (i = 0; i < table->size; i++)
		clear_list(table->buckets[i]);
}

void destroy_hash_table(hash_table *table)
{
	int i;
	for (i = 0; i < table->size; i++)
		destroy_list(&table->buckets[i]);
	free(table->buckets);
}

int print_bucket(hash_table *table, int index, FILE *output_file)
{
	if (index < 0 && index > table->size)
		return -1;

	print_list(table->buckets[index], output_file);
	return 0;
}

void print_hash_table(hash_table *table, FILE *output_file)
{
	int i;
	for (i = 0; i < table->size; i++)
		print_list(table->buckets[i], output_file);
}