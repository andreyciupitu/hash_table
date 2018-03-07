#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "hash_table.h"

#define DIE(assertion, call_description)								\
	do {												\
		if (assertion) {									\
			fprintf(stderr, "(%s, %d): ",							\
				__FILE__, __LINE__);							\
			perror(call_description);							\
			exit(errno);									\
		}											\
	} while (0)

int main(int argc, char *argv[])
{
	int i;
	char buffer[20001];
	char *token;
	if (argc >= 2)
		for (i = 2; i < argc; i++) {
			FILE *fin = fopen(argv[i], "r");

			/* Jump over the next file if the
			   current one can't be opened */
			if (fin == NULL)
				continue;

			fgets(buffer, 20000, fin);
			buffer[strlen(buffer) - 1] = 0;
			//parse_command(buffer);

			fclose(fin);
		}
	int size;
	sscanf(argv[1], "%d", &size);
	hash_table t;
	init_hash_table(&t, size);
	add_to_hash_table(&t, "cacat");
	add_to_hash_table(&t, "cacat");
	add_to_hash_table(&t, "mizerie");
	add_to_hash_table(&t, "pisat");
	add_to_hash_table(&t, "pula");
	print_hash_table(&t, stdout);
	resize_hash_table(&t, size / 2);
	print_hash_table(&t, stdout);
	resize_hash_table(&t, size * 2);
	print_hash_table(&t, stdout);
	remove_from_hash_table(&t, "cacat");
	print_bucket(&t, 0, stdout);
	print_hash_table(&t, stdout);
	clear_hash_table(&t);
	print_hash_table(&t, stdout);
	destroy_hash_table(&t);
	return 0;
}

void parse_command(hash_table *table, char *cmd)
{
	char *token;
	FILE *fout = stdout;
	int tmp;
	token = strtok(cmd, " ");

	if (strcmp(token, "add") == 0)
		add_to_hash_table(table, strtok(NULL, " "));

	if (strcmp(token, "remove") == 0)
		remove_from_hash_table(table, strtok(NULL, " "));

	if (strcmp(token, "find") == 0) {
		token = strtok(NULL, " ");

		tmp = contained_in_hash_table(table, token);

		token = strtok(NULL, " ");

		if (token != NULL) {
			fout = fopen(token, "a");
			DIE(fout == NULL, "Error opening file: ");
		}

		if (tmp) 
			fprintf(fout, "True\n");
		else
			fprintf(fout, "False\n");
	}

	if (strcmp(token, "clear") == 0)
		clear_hash_table(table);

	if (strcmp(token, "resize") == 0) {
		token = strtok(NULL, " ");
		if (strcmp(token, "double") == 0)
			resize_hash_table(table, table->size * 2);
		if (strcmp(token, "halve") == 0)
			resize_hash_table(table, table->size / 2);
	}

	if (strcmp(token, "print") == 0) {
		token = strtok(NULL, " ");

		if (token != NULL) {
			fout = fopen(token, "a");
			DIE(fout == NULL, "Error opening file: ");
		}

		print_hash_table(table, fout);
	}
	
	if (strcmp(token, "print_bucket") == 0) {
		token = strtok(NULL, " ");
		sscanf(token, "%d", &tmp);

		if (token != NULL) {
			fout = fopen(token, "a");
			DIE(fout == NULL, "Error opening file: ");
		}

		print_bucket(table, tmp, fout);
	}
}



