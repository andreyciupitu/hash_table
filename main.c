#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "utils.h"
#include "hash.h"

#define BUFSIZE 20000

static hash_table *parse_command(hash_table *table, char *cmd);

int main(int argc, char *argv[])
{
	int i;
	char buffer[BUFSIZE];
	unsigned int size;
	FILE *fin;
	hash_table *t;
	int status = 0;

	/*
	 * Check for corrent number of argumets
	 */
	CUSTOM_DIE(argc < 2, "Usage: ./tema1 SIZE [INPUT_FILES]",
		INVALID_PARAMETERS);

	/*
	 * Init the hash table
	 */
	status = sscanf(argv[1], "%u", &size);
	CUSTOM_DIE(status <= 0, "Size argument must be a positive number",
		INVALID_PARAMETERS);
	t = new_hash_table(size, hash);

	status = 0;
	if (argc > 2)
		for (i = 2; i < argc; i++) {
			fin = fopen(argv[i], "r");

			/*
			 * Jump to the next file if the
			 * current one can't be opened
			 */
			if (fin == NULL)
				continue;

			while (fgets(buffer, BUFSIZE, fin) != NULL)
				t = parse_command(t, buffer);

			status = fclose(fin);
			DIE(status < 0, "Error closing file");
		}
	else
		while (fgets(buffer, BUFSIZE, stdin) != NULL)
			t = parse_command(t, buffer);

	destroy_hash_table(t);
	return status;
}

static hash_table *parse_command(hash_table *table, char *buffer)
{
	char *cmd, *parameter;
	FILE *fout = stdout;
	int tmp;
	char sep[] = " \n";
	int status = 0;

	cmd = strtok(buffer, sep);

	/*
	 * Check for empty line
	 */
	if (cmd == NULL)
		return table;

	/*
	 * Add command
	 */
	if (strcmp(cmd, "add") == 0) {
		parameter = strtok(NULL, sep);
		CUSTOM_DIE(parameter == NULL, "Invalid Command",
			INVALID_ARGUMENT);
		add_to_hash_table(table, parameter);
		return table;
	}

	/*
	 * Remove command
	 */
	if (strcmp(cmd, "remove") == 0) {
		parameter = strtok(NULL, sep);
		CUSTOM_DIE(parameter == NULL, "Invalid Command",
			INVALID_ARGUMENT);
		remove_from_hash_table(table, parameter);
		return table;
	}

	/*
	 * Find command
	 */
	if (strcmp(cmd, "find") == 0) {
		parameter = strtok(NULL, sep);
		CUSTOM_DIE(parameter == NULL, "Invalid Command",
			INVALID_ARGUMENT);
		tmp = contained_in_hash_table(table, parameter);

		/*
		 * Check for output files
		 */
		parameter = strtok(NULL, sep);
		if (parameter != NULL) {
			fout = fopen(parameter, "a");
			DIE(fout == NULL, "Error opening file");
		}

		if (tmp)
			fprintf(fout, "True\n");
		else
			fprintf(fout, "False\n");

		/*
		 * Close output files, if any
		 */
		if (parameter != NULL) {
			status = fclose(fout);
			DIE(status < 0, "Error closing file");
		}
		return table;
	}

	/*
	 * Clear command
	 */
	if (strcmp(cmd, "clear") == 0) {
		clear_hash_table(table);
		return table;
	}

	/*
	 * Resize command
	 */
	if (strcmp(cmd, "resize") == 0) {
		parameter = strtok(NULL, sep);
		CUSTOM_DIE(parameter == NULL, "Invalid Command",
			INVALID_ARGUMENT);

		if (strcmp(parameter, "double") == 0) {
			table = resize_hash_table(table, table->size * 2);
			return table;
		}
		if (strcmp(parameter, "halve") == 0) {
			table = resize_hash_table(table, table->size / 2);
			return table;
		}
	}

	/*
	 * Print
	 */
	if (strcmp(cmd, "print") == 0) {
		/*
		 * Check for output files
		 */
		parameter = strtok(NULL, sep);
		if (parameter != NULL) {
			fout = fopen(parameter, "a");
			DIE(fout == NULL, "Error opening file");
		}

		print_hash_table(table, fout);

		/*
		 * Close output files, if any
		 */
		if (parameter != NULL) {
			status = fclose(fout);
			DIE(status < 0, "Error closing file");
		}
		return table;
	}

	/*
	 * Print bucket
	 */
	if (strcmp(cmd, "print_bucket") == 0) {
		parameter = strtok(NULL, sep);
		CUSTOM_DIE(parameter == NULL, "Invalid Command",
			INVALID_ARGUMENT);
		status = sscanf(parameter, "%u", &tmp);
		CUSTOM_DIE(status <= 0, "Index must be a positive number",
			INVALID_ARGUMENT);

		/*
		 * Check for output files
		 */
		parameter = strtok(NULL, sep);
		if (parameter != NULL) {
			fout = fopen(parameter, "a");
			DIE(fout == NULL, "Error opening file");
		}

		print_bucket(table, tmp, fout);

		/*
		 * Close output files, if any
		 */
		if (parameter != NULL) {
			status = fclose(fout);
			DIE(status < 0, "Error closing file");
		}
		return table;
	}

	fprintf(stderr, "Invalid command\n");
	exit(INVALID_COMMAND);
}
