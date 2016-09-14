/**
 * \file 	ll.h
 * \author 	Richard Degenne
 * \date 	13-09-16
 *
 * \brief 	Header file for the ll module
 *
 * This file defines the structure and interface of a linked list
 * library.
 */

#ifndef _LL_H
#define _LL_H

#include <stdlib.h>


/**
 * \brief 	Comparison function
 * 
 * This function is used for searching elements. It must return an @int :
 * 0 if the elements are equal, any other value otherwise.
 *
 * \see ll_remove
 * \see ll_search
 */
typedef int (*compareFun)(void *, void *);


/**
 * \brief 	Free function
 *
 * This function type allows the user to specify a way to dynamically
 * deallocate memory when a list node is destroyed, to avoid memory leaks.
 */
typedef void (*freeFun)(void *);


/**
 * \brief 	Iteration function
 *
 * This function type is used when iterating over a linked list's elements.
 *
 * \see 	bst_iter
 */
typedef void (*iterFun)(void *);


/**
 * \brief 	Node structure
 *
 * This describes the structure of a node. The ll_node#data type is @c void*
 * to be as generic as possible. See the @c ll structure for further details about
 * how is implemented the list data type.
 *
 * \see 	bst
 */
typedef struct _ll_node {
	void* data; 	/**< The node's data */
	struct _ll_node* next; 	/**< The node's next node */
} ll_node;


/**
 * \brief 	Linked list structure
 *
 * This is the structure of a linked list.
 *
 * \warning 	Do not manipulate the structure directly. Use the functions of the
 * ll interface instead.
 */
typedef struct {
	size_t data_size; /**< Size of an element */
	bst_node* head; /**< Head of the linked list */
	compareFun compare; /**< Comparison function */
	freeFun free; /**< Dynamic deallocation of tree data */
} ll;


/**
 * \brief 	Initializes a list
 *
 * Use this function to initialize the list attributes. Make sure you respect
 * the following conditions since some @c asserts are used to check the
 * parameters relevance.
 *
 * \param 	data_size 	The size of an element; must be > 0.
 * \param 	free_fun 	The tree's data freeing function; can be NULL.
 *
 * \return 	A pointer to the_newly-allocated tree.
 *
 * \warning 	Breaking any of the above conditions will cause the program to
 * abort!
 */
ll* ll_new(size_t data_size, compareFun compare_fun, freeFun free_fun);


/**
 * \brief 	Destroys a list
 *
 * A call to ll_destroy deallocates a linked list and all its nodes by calling
 * ll#free. Make sure the program calls it when the list is not needed anymore.
 *
 * \param 	list 	The list to deallocate
 *
 * \warning 	Not using this function to deallocate a ll will cause memory
 * leaks!
 * */
void ll_destroy(ll* tree);


/**
 * \brief 	Adds a new node at the beginning of the list
 *
 * Calling this function dynamically allocates a new node and inserts it into
 * the binary search tree.
 *
 * \param 	list 	The list to insert the new node into. Cannot be @c NULL
 * \param 	element 	The new node's data. Cannot be @c NULL
 *
 * \warning 	Breaking any of the above conditions will cause the program to
 * abort!
 */
void ll_add_head(ll* tree, void* element);


/**
 * \brief 	Adds a new node after a given node
 *
 * Calling this function dynamically allocates a new node and inserts it after
 * the @c node node
 *
 * \param 	list 	The list to insert the new node into. Cannot be @c NULL
 * \param 	element 	The new node's data. Cannot be @c NULL
 *
 * \warning 	Breaking any of the above conditions will cause the program to
 * abort!
 */
void ll_add_after(ll* tree, void* element);


/**
 * \brief 	Computes the size of a list
 *
 * \param 	list 	List to compute
 *
 * \return 	The number of elements in the list
 */
int ll_size(ll* list);


/**
 * \brief 	Searches a list
 *
 * Searches @c list for @c element. A node is considered a result whenever ll#compare
 * returns 0.
 *
 * \param 	list 	The list to search
 * \param 	element 	The element to search for
 *
 * \return 	A pointer to the node element was found, @c NULL if element
 * couldn't be found.
 *
 * \see 	ll#compare
 * \see 	compareFun
 * */
ll_node* ll_search(ll* list, void* element);


/**
 * \brief 	Iterates over a list
 *
 * Applies a function to every element in the list.
 *
 * \param 	list 	The list to iterate over
 * \param 	function 	The function to apply. Cannot be @c NULL.
 */
void ll_iter(ll* list, iterFun function);


/**
 * \brief 	Removes an element
 *
 * Removes a node (using ll#free to dynamically deallocate the node's data if
 * needed), and restores the list structure. If there are several occurences of
 * element in tree, only the one closest to the head will be removed.
 * 
 * \param 	list 	List to remove element from
 * \param 	element 	Element to remove
 */
void ll_remove(ll* tree, void* element);


#endif
