#ifndef HASH_TABLE_H
#define HASH_TABLE_H 1

#include <stdio.h>

#include "list.h"

typedef unsigned int (*hash_func)(const char*, unsigned int);

typedef struct hash_table {
	list *buckets;
	unsigned int size;
	hash_func hash;
} hash_table;

/**
 *  @brief Creates a new hash table
 *
 *  @param [in] size The number of buckets in the hash table
 *  @param [in] hash The hash function used by the hash_table
 *  @return A pointer to the new hash table
 */
hash_table *new_hash_table(unsigned int size, hash_func hash);

/**
 *  @brief Deallocates the memory used by a hash_table
 *
 *  @param [in] table A pointer to a hash table
 *
 *  @details Before destroying the hash table the function
 *  performs a clear to free the data in the buckets
 */
void destroy_hash_table(hash_table *table);

/**
 *  @brief Adds a new element to the hash table
 *
 *  @param [in] table A pointer to the hash table
 *  @param [in] data  The data to be added
 */
void add_to_hash_table(hash_table *table, char *data);

/**
 *  @brief Removes an element from the hash table
 *
 *  @param [in] table A pointer to the hash table
 *  @param [in] data  The element to be removed
 */
void remove_from_hash_table(hash_table *table, char *data);

/**
 *  @brief Checks if the element is in the hash table
 *
 *  @param [in] table A pointer to the hash table
 *  @param [in] data  The element to be found
 *  @return 1 if the element is found, 0 otherwise
 */
int contained_in_hash_table(hash_table *table, char *data);

/**
 *  @brief Removes all data from the hash table
 *
 *  @param [in] table A pointer to the hash table
 */
void clear_hash_table(hash_table *table);

/**
 *  @brief Resizes the hash table, reassigning the elements
 *
 *  @param [in] table A pointer to the hash table
 *  @param [in] size  The new size
 *  @return A pointer to the resized hash table
 *
 *  @details The function will create a new hash table with
 *  the new size and the same hash function and will move
 *  the data from the old hash table. The old hash table
 *  is destroyed.
 */
hash_table *resize_hash_table(hash_table *table, unsigned int size);

/**
 *  @brief Prints the selected bucket
 *
 *  @param [in] table       A pointer to the hash table
 *  @param [in] index       The index of the bucket
 *  @param [in] output_file The output file
 */
void print_bucket(hash_table *table, unsigned int index, FILE *output_file);

/**
 *  @brief Prints the data in the hash table
 *
 *  @param [in] table       A pointer to the hash table
 *  @param [in] output_file The output file
 */
void print_hash_table(hash_table *table, FILE *output_file);

#endif
