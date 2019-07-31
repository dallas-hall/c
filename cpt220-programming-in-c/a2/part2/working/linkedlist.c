/******************************************************************************
 * Student Name    :  Dallas Hall
 * RMIT Student ID :  s3461243
 * COURSE CODE     :  CPT220 / OLA00
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2019.
 *****************************************************************************/

#include "linkedlist.h"

/**
 * implement the functions for managing the linked list here
 **/
/*
 * My linked list code comes from week 8 and 9 tutorial code as well
 * as C How To Program 6e chapter 12.
 *
 * I did the tutorials in the textbook for linked list, doubly linked list,
 * stacks, queues, and binary search trees. They were all conceptually similar.
 */
struct linkedlist* createLinkedList(struct linkedlist* theLinkedListPtr)
{
	/*
	 * mallac tries to allocate memory with the specified bytes.
	 * sizeof will return the size of the data structure, platform dependent.
	 * If successful, malloc returns a void * to the allocated memory, otherwise
	 * returns NULL
	 *
	 * We are using struct linkedlist because that is the object that will be
	 * stored in the pointer.
	 *
	 * Paul tends to cast the void* returned by malloc.
	 */
	theLinkedListPtr = malloc(sizeof(struct linkedlist));

	/*
	 * Same as theLinkedListPtr == NULL. I tend to use both.
	 */
	if (!theLinkedListPtr) {
		return NULL;
	}
	else {
		theLinkedListPtr->head = NULL;
		theLinkedListPtr->size = 0;
	}

	return theLinkedListPtr;
}

BOOLEAN insertNode(struct linkedlist* theLinkedListPtr,
				   struct node* theGameResultNodePrt)
{
	/*
	 * TODO
	 *
	 * Insert in descending order
	 * Update links and counter
	 */
	

	return FALSE;
}

BOOLEAN deleteNode(struct linkedlist* theLinkedListPtr,
				   struct node* theGameResultNodePrt)
{
	/*
	 * TODO
	 *
	 * Delete a node
	 */
	return FALSE;
}

BOOLEAN findNode(struct linkedlist* theLinkedListPtr, struct node* theNodePtr)
{
	/*
	 * TODO
	 *
	 * find a node
	 */
	return FALSE;
}

/*
 * This is basically a debug print.
 * It prints from the head to the tail, one node per line.
 */
void prettyPrintLinkedList(struct linkedlist* theLinkedListPtr)
{
	/*
	 * TODO
	 *
	 * print the linked list in order
	 */
}

/*
 * This will be the function to write the linked out to disk in a csv format.
 */
void csvPrintLinkedList(struct linkedlist* theLinkedListPtr, char delimiter)
{
	/*
	 * TODO
	 *
	 * print the linked list in order in CSV format
	 */
}

BOOLEAN deleteLinkedList(struct linkedlist* theLinkedListPtr)
{
	return FALSE;
}