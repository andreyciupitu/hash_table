#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "utils.h"

void init_list(list *head)
{
	/*
	 * Create a dummy node for easier processing
	 */
	*head = calloc(1, sizeof(struct node));
	DIE(*head == NULL, "Memory alloc error in bucket initialization");
}

void add_element(list head, char *data)
{
	struct node *it, *new;

	it = head;
	while (it->next != NULL)
		it = it->next;

	/*
	 * Create the new node
	 */
	new = malloc(sizeof(struct node));
	DIE(new == NULL, "Memory alloc error in add");
	new->data = calloc(strlen(data) + 1, sizeof(char));
	strncpy(new->data, data, strlen(data));
	DIE(new->data == NULL, "Memory alloc error in add");
	new->next = NULL;

	/*
	 * Add the new node to the end
	 */
	it->next = new;
}

void remove_element(list head, char *data)
{
	struct node *it, *prev_it;

	prev_it = head;
	it = head->next;
	while (it != NULL) {
		if (strcmp(data, it->data) == 0) {
			/*
			 * Remove the node and free memory
			 */
			prev_it->next = it->next;
			free(it->data);
			free(it);
			return;
		}
		prev_it = it;
		it = it->next;
	}
}

int contains_element(list head, char *data)
{
	struct node *it;

	/*
	 * Jump over dummy node
	 */
	it = head->next;

	while (it != NULL) {
		if (strcmp(data, it->data) == 0)
			return 1;
		it = it->next;
	}

	return 0;
}

void print_list(list head, FILE *output_file)
{
	struct node *it;

	/*
	 * Jump over dummy node
	 */
	it = head->next;

	/*
	 * Don't print anything for an empty list
	 */
	if (it == NULL)
		return;

	while (it->next != NULL) {
		fprintf(output_file, "%s ", it->data);
		it = it->next;
	}
	fprintf(output_file, "%s\n", it->data);
}

void clear_list(list head)
{
	struct node *tmp;
	struct node *it;

	/*
	 * Jump over dummy node
	 */
	it = head->next;

	while (it != NULL) {
		tmp = it->next;
		free(it->data);
		free(it);
		it = tmp;
	}

	/*
	 * Reset dummy node
	 */
	head->next = NULL;
}

void destroy_list(list *head)
{
	clear_list(*head);
	free(*head);
	*head = NULL;
}
