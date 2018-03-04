#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void init_list(struct list **head)
{
	/* Create a dummy node for easier processing */
	*head = (struct list*)calloc(1, sizeof(struct list));
}

void add_element(struct list *head, char *data)
{
	struct list *it, *new;
	
	it = head;
	while (it->next != NULL)
		it = it->next;
	
	/* Create the new node */
	new = (struct list*)malloc(sizeof(struct list));
	strncpy(new->data, data, strlen(data));
	new->data[strlen(data)] = 0;
	new->next = NULL;
	
	/* Add the new node to the end */
	it->next = new;
}

void remove_element(struct list *head, char *data)
{
	struct list *it, *prev_it;

	prev_it = head;
	it = head->next;
	while (it != NULL) {
		if (strcmp(data, it->data) == 0) {
			
			/* Remove the node and free memory */
			prev_it->next = it->next;
			free(it);
			return;
		}
		prev_it = it;
		it = it->next;
	}
}

struct list *find_element(struct list *head, char *data)
{
	struct list *it = head->next;
	
	while (it != NULL) {
		if (strcmp(data, it->data) == 0) {
			return it;
		}
		it = it->next;
	}
	
	return NULL;
}

void print_list(struct list *head, FILE *output_file)
{
	/* Jump over dummy node */
	head = head->next;
	
	/* Don't print anything for an empty list */
	if (head == NULL)
		return;
	
	while (head->next != NULL) {
		fprintf(output_file, "%s ", head->data);
		head = head->next;
	}
	fprintf(output_file, "%s\n", head->data);
}

void clear_list(struct list *head)
{
	struct list *tmp;
	struct list *it;
	
	/* Jump over dummy node */
	it = head->next;

	while (it != NULL) {
		tmp = it->next;
		free(it);
		it = tmp;
	}
	
	/* Reset dummy node */
	head->next = NULL;
}

void destroy_list(struct list **head)
{
	clear_list(*head);
	free(*head);
	*head = NULL;
}