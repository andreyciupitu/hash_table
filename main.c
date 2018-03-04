#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "list.h"

#define DIE(assertion, call_description)				\
	do {												\
		if (assertion) {								\
			fprintf(stderr, "(%s, %d): ",				\
					__FILE__, __LINE__);				\
			perror(call_description);					\
			exit(errno);								\
		}												\
	} while (0)
		

int main(int argc, char *argv[])
{
	int i;
	if (argc >= 2)
		for (i = 2; i < argc; i++) {
			FILE *fin = fopen(argv[i], "r");
			DIE(fin == NULL, "Cannot open file provided as argument");
			
			fclose(fin);
		}
	struct list *l;
	init_list(&l);
	add_element(l, "cacat");
	add_element(l, "pisat");
	add_element(l, "mizerie");
	print_list(l, stdout);
	remove_element(l, "pisat");
	print_list(l, stdout);
	remove_element(l, "cacat");
	print_list(l, stdout);
	clear_list(l);
	print_list(l, stdout);
	remove_element(l, "cacat");
	add_element(l, "cacat");
	print_list(l, stdout);
	destroy_list(&l);
	return 0;
}