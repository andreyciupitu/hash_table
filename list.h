#ifndef LIST_H
#define LIST_H 1

#include <stdio.h>

struct list {
	char data[100];
	struct list* next;
};

/**
 *  @brief Initializes a list
 *  
 *  @param [in] head The list
 *  
 *  @details Will allocate memory for the head of the list
 */
void init_list(struct list **head);

/**
 *  @brief Adds a word to the list
 *  
 *  @param [in] head The list
 *  @param [in] data The string to be added to the list
 */
void add_element(struct list *head, char *data);

/**
 *  @brief Removes the string from the list
 *  
 *  @param [in] head The list
 *  @param [in] data The string to be removed
 */
void remove_element(struct list *head, char *data);

/**
 *  @brief Finds an element in a list.
 *  
 *  @param [in] head The list
 *  @param [in] data The element to search for
 *  @return A pointer to the node containing the element.
 *  		Returns NULL if the element is not in the list.
 */
struct list *find_element(struct list *head, char *data);

/**
 *  @brief Prints all the string in the given list
 *  
 *  @param [in] head        The list 
 *  @param [in] output_file The output file
 */
void print_list(struct list *head, FILE *output_file);

/**
 *  @brief Removes all the elements of a list
 *  
 *  @param [in] head The list
 */
void clear_list(struct list *head);

/**
 *  @brief Removes and deallocates all the elements of the list
 *  
 *  @param [in] head The list
 *  
 *  @details After calling this function head will be set to NULL
 */
void destroy_list(struct list **head);

#endif //LIST_H