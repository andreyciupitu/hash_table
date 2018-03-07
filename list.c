#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void init_list(list *head)
{
	/* Create a dummy node for easier processing */
	*head = (struct node*)calloc(1, sizeof(struct node));
	if (*head == NULL)
		return;
}

void add_element(list head, char *data)
{
	struct node *it, *new;

	it = head;
	while (it->next != NULL)
		it = it->next;

	/* Create the new node */
	new = (struct node*)malloc(sizeof(struct node));
	if (new == NULL)
		return;
	new->data = strdup(data);
	if (new->data == NULL)
		return;
	new->next = NULL;

	/* Add the new node to the end */
	it->next = new;
}

void remove_element(list head, char *data)
{
	struct node *it, *prev_it;

	prev_it = head;
	it = head->next;
	while (it != NULL) {
		if (strcmp(data, it->data) == 0) {
			/* Remove the node and free memory */
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
	/* Jump over dummy node */
	struct node *it = head->next;

	while (it != NULL) {
		if (strcmp(data, it->data) == 0)
			return 1;
		it = it->next;
	}

	return 0;
}

void print_list(list head, FILE *output_file)
{
	/* Jump over dummy node */
	struct node *it = head->next;

	/* Don't print anything for an empty list */
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

	/* Jump over dummy node */
	it = head->next;

	while (it != NULL) {
		tmp = it->next;
		free(it->data);
		free(it);
		it = tmp;
	}

	/* Reset dummy node */
	head->next = NULL;
}

void destroy_list(list *head)
{
	clear_list(*head);
	free(*head);
	*head = NULL;
}